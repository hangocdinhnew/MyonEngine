#include "MyonCore/Graphics/Vulkan/VulkanGraphicsPipeline.hpp"
#include <shaderc/shaderc.hpp>

namespace MyonCore {
VulkanGraphicsPipeline::VulkanGraphicsPipeline(vk::Device p_Device,
                                               const std::string vert,
                                               const std::string frag)
    : m_Device(p_Device) {
  auto vertShaderCode = readFile(vert);
  auto fragShaderCode = readFile(frag);

  std::vector<uint32_t> vertSPIRV =
      compileGLSL(vertShaderCode, shaderc_glsl_vertex_shader, "Vertex");
  std::vector<uint32_t> fragSPIRV =
      compileGLSL(fragShaderCode, shaderc_glsl_fragment_shader, "Fragment");

  vk::ShaderModule vertShaderModule = createShaderModule(vertSPIRV);
  vk::ShaderModule fragShaderModule = createShaderModule(fragSPIRV);

  vk::PipelineShaderStageCreateInfo vertShaderStageInfo{};
  vertShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
  vertShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  vk::PipelineShaderStageCreateInfo fragShaderStageInfo{};
  fragShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
  fragShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  vk::PipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo,
                                                      fragShaderStageInfo};

  m_Device.destroyShaderModule(fragShaderModule, nullptr);
  m_Device.destroyShaderModule(vertShaderModule, nullptr);

  MYON_CORE_INFO("Shader modules created and destroyed!");
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline() {}

std::string VulkanGraphicsPipeline::readFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    MYON_DO_CORE_ASSERT("Failed to open file - {}", filename);
  }

  size_t fileSize = (size_t)file.tellg();
  std::string buffer(fileSize, ' ');

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return buffer;
}

std::vector<uint32_t> VulkanGraphicsPipeline::compileGLSL(const std::string &source,
                                  shaderc_shader_kind kind,
                                  const std::string &name) {
  shaderc::Compiler compiler;
  shaderc::CompileOptions options;

  // Performance optimization (optional)
  options.SetOptimizationLevel(shaderc_optimization_level_performance);

  auto result =
      compiler.CompileGlslToSpv(source, kind, name.c_str(), options);

  if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
    MYON_DO_CORE_ASSERT("Shader compilation failed - {}",
                        result.GetErrorMessage());
  }

  return {result.cbegin(), result.cend()};
}

vk::ShaderModule
VulkanGraphicsPipeline::createShaderModule(const std::vector<uint32_t> &code) {
  vk::ShaderModuleCreateInfo createInfo{};
  createInfo.sType = vk::StructureType::eShaderModuleCreateInfo;
  createInfo.codeSize = code.size() * sizeof(uint32_t);
  createInfo.pCode = code.data();

  vk::ShaderModule shaderModule;
  if (m_Device.createShaderModule(&createInfo, nullptr, &shaderModule) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create shader module!");
  }

  return shaderModule;
}

} // namespace MyonCore

#include "MyonCore/Graphics/Vulkan/VulkanGraphicsPipeline.hpp"
#include <shaderc/shaderc.hpp>

namespace MyonCore {
VulkanGraphicsPipeline::VulkanGraphicsPipeline(vk::Device p_Device,
                                               vk::RenderPass p_RenderPass,
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

  vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
  vertexInputInfo.sType =
      vk::StructureType::ePipelineVertexInputStateCreateInfo;
  vertexInputInfo.vertexBindingDescriptionCount = 0;
  vertexInputInfo.pVertexBindingDescriptions = nullptr;
  vertexInputInfo.vertexAttributeDescriptionCount = 0;
  vertexInputInfo.pVertexAttributeDescriptions = nullptr;

  vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType =
      vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
  inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
  inputAssembly.primitiveRestartEnable = vk::False;

  vk::PipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
  viewportState.viewportCount = 1;
  viewportState.scissorCount = 1;

  vk::PipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
  rasterizer.depthClampEnable = vk::False;
  rasterizer.rasterizerDiscardEnable = vk::False;
  rasterizer.polygonMode = vk::PolygonMode::eFill;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = vk::CullModeFlagBits::eBack;
  rasterizer.frontFace = vk::FrontFace::eClockwise;
  rasterizer.depthBiasEnable = vk::False;

  vk::PipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
  multisampling.sampleShadingEnable = vk::False;
  multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
  multisampling.minSampleShading = 1.0f;
  multisampling.pSampleMask = nullptr;
  multisampling.alphaToCoverageEnable = vk::False;
  multisampling.alphaToOneEnable = vk::False;

  vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask =
      vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
      vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
  colorBlendAttachment.blendEnable = vk::False;
  colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eOne;
  colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero;
  colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
  colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
  colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
  colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

  vk::PipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;
  colorBlending.logicOpEnable = vk::False;
  colorBlending.logicOp = vk::LogicOp::eCopy;
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f;
  colorBlending.blendConstants[1] = 0.0f;
  colorBlending.blendConstants[2] = 0.0f;
  colorBlending.blendConstants[3] = 0.0f;

  std::vector<vk::DynamicState> dynamicStates = {vk::DynamicState::eViewport,
                                                 vk::DynamicState::eScissor};

  vk::PipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
  dynamicState.dynamicStateCount = dynamicStates.size();
  dynamicState.pDynamicStates = dynamicStates.data();

  vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 0;
  pipelineLayoutInfo.pPushConstantRanges = nullptr;

  if (m_Device.createPipelineLayout(&pipelineLayoutInfo, nullptr,
                                    &m_PipelineLayout) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create Pipeline Layout!");
  }

  vk::GraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages;
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = nullptr;
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;
  pipelineInfo.layout = m_PipelineLayout;
  pipelineInfo.renderPass = p_RenderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = nullptr;
  pipelineInfo.basePipelineIndex = -1;

  if (m_Device.createGraphicsPipelines(nullptr, 1, &pipelineInfo, nullptr,
                                       &m_GraphicsPipeline) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create Graphics pipeline!");
  }

  m_Device.destroyShaderModule(fragShaderModule, nullptr);
  m_Device.destroyShaderModule(vertShaderModule, nullptr);
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline() {
  m_Device.destroyPipeline(m_GraphicsPipeline, nullptr);
  m_Device.destroyPipelineLayout(m_PipelineLayout, nullptr);
}

void VulkanGraphicsPipeline::cleanup() {
  m_Device.destroyPipeline(m_GraphicsPipeline, nullptr);
  m_Device.destroyPipelineLayout(m_PipelineLayout, nullptr);
}

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

std::vector<uint32_t>
VulkanGraphicsPipeline::compileGLSL(const std::string &source,
                                    shaderc_shader_kind kind,
                                    const std::string &name) {
  shaderc::Compiler compiler;
  shaderc::CompileOptions options;

  // Performance optimization (optional)
  options.SetOptimizationLevel(shaderc_optimization_level_performance);

  auto result = compiler.CompileGlslToSpv(source, kind, name.c_str(), options);

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

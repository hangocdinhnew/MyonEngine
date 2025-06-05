#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

#include <fstream>
#include <shaderc/shaderc.hpp>
#include <vulkan/vulkan.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanGraphicsPipelineConfig {
  vk::Device p_Device;
  vk::RenderPass p_RenderPass;
  std::string p_Vert;
  std::string p_Frag;
  vk::DescriptorSetLayout p_DescriptorSetLayout;
};

class VulkanGraphicsPipeline {
public:
  VulkanGraphicsPipeline(
      VulkanGraphicsPipelineConfig &p_GraphicsPipelineConfig);
  ~VulkanGraphicsPipeline();

  vk::PipelineLayout &getPipelineLayout() { return m_PipelineLayout; }
  vk::Pipeline &getGraphicsPipeline() { return m_GraphicsPipeline; }

  void cleanup();

private:
  vk::Device &m_Device;

  std::string readFile(const std::string &filename);
  static std::vector<uint32_t> compileGLSL(const std::string &source,
                                           shaderc_shader_kind kind,
                                           const std::string &name = "shader");

  vk::ShaderModule createShaderModule(const std::vector<uint32_t> &code);

  vk::PipelineLayout m_PipelineLayout;
  vk::Pipeline m_GraphicsPipeline;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

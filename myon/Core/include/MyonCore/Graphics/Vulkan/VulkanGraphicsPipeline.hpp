#include "MyonCore/Core/Log.hpp"

#include <fstream>
#include <shaderc/shaderc.hpp>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanGraphicsPipeline {
public:
  VulkanGraphicsPipeline(vk::Device p_Device, vk::RenderPass p_RenderPass,
                         const std::string vert, const std::string frag);
  ~VulkanGraphicsPipeline();

  vk::Pipeline getGraphicsPipeline() { return m_GraphicsPipeline; }

  void cleanup();

private:
  vk::Device m_Device;

  std::string readFile(const std::string &filename);
  static std::vector<uint32_t> compileGLSL(const std::string &source,
                                           shaderc_shader_kind kind,
                                           const std::string &name = "shader");

  vk::ShaderModule createShaderModule(const std::vector<uint32_t> &code);

  vk::PipelineLayout m_PipelineLayout;
  vk::Pipeline m_GraphicsPipeline;
};
} // namespace MyonCore

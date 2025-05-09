#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanRenderPassConfig {
  vk::Device p_Device;
  vk::Format p_SwapchainImageFormat;
};

class VulkanRenderPass {
public:
  VulkanRenderPass(VulkanRenderPassConfig &p_RenderPassConfig);
  ~VulkanRenderPass();

  vk::RenderPass &getRenderPass() { return m_RenderPass; }

  void cleanup();

private:
  vk::Device &m_Device;

  vk::RenderPass m_RenderPass;
};
} // namespace MyonCore

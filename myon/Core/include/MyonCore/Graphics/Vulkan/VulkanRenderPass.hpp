#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanRenderPass {
public:
  VulkanRenderPass(vk::Device p_Device, vk::Format p_SwapchainImageFormat);
  ~VulkanRenderPass();

private:
  vk::Device m_Device;

  vk::RenderPass m_RenderPass;
};
} // namespace MyonCore

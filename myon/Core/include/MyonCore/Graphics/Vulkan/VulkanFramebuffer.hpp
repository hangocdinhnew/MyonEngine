#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanFramebuffer {
public:
  VulkanFramebuffer(vk::Device p_Device, vk::RenderPass p_RenderPass,
                    std::vector<vk::ImageView> p_SwapChainImageViews,
                    vk::Extent2D p_SwapChainExtent);
  ~VulkanFramebuffer();

  std::vector<vk::Framebuffer> getSwapchainFramebuffers() {
    return m_SwapchainFramebuffers;
  };

  void cleanup();

private:
  vk::Device m_Device;

  std::vector<vk::Framebuffer> m_SwapchainFramebuffers;
};
} // namespace MyonCore

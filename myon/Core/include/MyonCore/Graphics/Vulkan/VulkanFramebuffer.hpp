#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanFramebufferConfig {
  vk::Device p_Device;
  vk::RenderPass p_RenderPass;
  std::vector<vk::ImageView> p_SwapChainImageViews;
  vk::Extent2D p_SwapChainExtent;
};

class VulkanFramebuffer {
public:
  VulkanFramebuffer(VulkanFramebufferConfig& p_FramebufferConfig);
  ~VulkanFramebuffer();

  std::vector<vk::Framebuffer> &getSwapchainFramebuffers() {
    return m_SwapchainFramebuffers;
  };

  void cleanup();

private:
  vk::Device &m_Device;

  std::vector<vk::Framebuffer> m_SwapchainFramebuffers;
};
} // namespace MyonCore

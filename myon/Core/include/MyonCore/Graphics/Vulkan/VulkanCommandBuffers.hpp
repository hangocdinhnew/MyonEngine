#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanCommandBufferConfig {
  vk::Device p_Device;
  vk::PhysicalDevice p_PhysicalDevice;
  vk::SurfaceKHR p_Surface;
  vk::RenderPass p_RenderPass;
  std::vector<vk::Framebuffer> p_SwapChainFramebuffers;
  vk::Extent2D p_SwapChainExtent;
  vk::Pipeline p_GraphicsPipeline;
};

class VulkanCommandBuffer {
public:
  VulkanCommandBuffer(VulkanCommandBufferConfig& p_CommandBufferConfig);
  ~VulkanCommandBuffer();

  void recordCommandBuffer(uint32_t imageIndex);

  vk::CommandPool &getCommandPool() { return m_CommandPool; }
  std::vector<vk::CommandBuffer> &getCommandBuffer() {
    return m_CommandBuffers;
  }

  void cleanup();

private:
  vk::Device &m_Device;

  vk::CommandPool m_CommandPool;
  std::vector<vk::CommandBuffer> m_CommandBuffers;

  std::vector<vk::Framebuffer> &m_SwapchainFramebuffers;
  vk::RenderPass &m_RenderPass;

  vk::Extent2D &m_SwapChainExtent;
  vk::Pipeline &m_GraphicsPipeline;
};
}
}
} // namespace MyonCore

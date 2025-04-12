#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanRenderer {
public:
  VulkanRenderer(vk::Device p_Device, vk::Queue p_GraphicsQueue,
                 vk::Queue p_PresentQueue, vk::SwapchainKHR p_SwapChain,
                 vk::CommandBuffer p_CommandBuffer, vk::RenderPass p_RenderPass,
                 vk::Pipeline p_GraphicsPipeline,
                 vk::Extent2D p_SwapChainExtent,
                 std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
                 vk::Semaphore p_ImageAvailableSemaphore,
                 vk::Semaphore p_RenderFinishedSemaphore,
                 vk::Fence p_InFlightFence);
  ~VulkanRenderer() = default;

  void DrawFrame();

private:
  vk::Device m_Device;

  vk::CommandBuffer m_CommandBuffer;
  vk::RenderPass m_RenderPass;
  vk::Pipeline m_GraphicsPipeline;
  vk::SwapchainKHR m_SwapChain;
  vk::Queue m_GraphicsQueue;
  vk::Queue m_PresentQueue;

  vk::Semaphore m_ImageAvailableSemaphore;
  vk::Semaphore m_RenderFinishedSemaphore;
  vk::Fence m_InFlightFence;

  vk::Extent2D m_SwapChainExtent;
  std::vector<vk::Framebuffer> m_SwapChainFramebuffers;

  void recordCommandBuffer(uint32_t imageIndex);
};
} // namespace MyonCore

#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanRenderer {
public:
  VulkanRenderer(vk::Device &p_Device, vk::Queue &p_GraphicsQueue,
                 vk::Queue &p_PresentQueue, vk::SwapchainKHR &p_SwapChain,
                 std::vector<vk::CommandBuffer> &p_CommandBuffers,
                 vk::RenderPass &p_RenderPass, vk::Pipeline &p_GraphicsPipeline,
                 vk::Extent2D &p_SwapChainExtent,
                 std::vector<vk::Framebuffer> &p_SwapChainFramebuffers,
                 std::vector<vk::Semaphore> &p_ImageAvailableSemaphores,
                 std::vector<vk::Semaphore> &p_RenderFinishedSemaphores,
                 std::vector<vk::Fence> &p_InFlightFences,
                 vk::Buffer &p_VertexBuffer, vk::Buffer &p_IndexBuffer);
  ~VulkanRenderer() = default;

  void DrawFrame();

  void
  UpdateSwapchain(vk::Queue &p_NewGraphicsQueue, vk::Queue &p_NewPresentQueue,
                  vk::SwapchainKHR &p_NewSwapChain,
                  std::vector<vk::CommandBuffer> &p_NewCommandBuffers,
                  vk::RenderPass &p_NewRenderPass,
                  vk::Pipeline &p_NewGraphicsPipeline,
                  vk::Extent2D &p_NewSwapChainExtent,
                  std::vector<vk::Framebuffer> &p_NewSwapChainFramebuffers,
                  std::vector<vk::Semaphore> &p_NewImageAvailableSemaphores,
                  std::vector<vk::Semaphore> &p_NewRenderFinishedSemaphores,
                  std::vector<vk::Fence> &p_NewInFlightFences);

  bool &ShouldRecreateSwapChain() { return m_ShouldRecreateSwapChain; };

  void ResetShouldRecreateSwapChain() { m_ShouldRecreateSwapChain = false; };

private:
  vk::Device &m_Device;

  std::vector<vk::CommandBuffer> m_CommandBuffers;
  vk::RenderPass m_RenderPass;
  vk::Pipeline m_GraphicsPipeline;
  vk::SwapchainKHR m_SwapChain;
  vk::Queue m_GraphicsQueue;
  vk::Queue m_PresentQueue;

  std::vector<vk::Semaphore> m_ImageAvailableSemaphores;
  std::vector<vk::Semaphore> m_RenderFinishedSemaphores;
  std::vector<vk::Fence> m_InFlightFences;

  vk::Extent2D m_SwapChainExtent;
  std::vector<vk::Framebuffer> m_SwapChainFramebuffers;

  vk::Buffer m_VertexBuffer;
  vk::Buffer m_IndexBuffer;

  void recordCommandBuffer(uint32_t imageIndex);

  uint32_t m_CurrentFrame = 0;

  bool m_ShouldRecreateSwapChain = false;
};
} // namespace MyonCore

#include "MyonCore/Graphics/Vulkan/VulkanRenderer.hpp"

namespace MyonCore {

VulkanRenderer::VulkanRenderer(
    vk::Device p_Device, vk::Queue p_GraphicsQueue, vk::Queue p_PresentQueue,
    vk::SwapchainKHR p_SwapChain,
    std::vector<vk::CommandBuffer> p_CommandBuffers,
    vk::RenderPass p_RenderPass, vk::Pipeline p_GraphicsPipeline,
    vk::Extent2D p_SwapChainExtent,
    std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
    std::vector<vk::Semaphore> p_ImageAvailableSemaphores,
    std::vector<vk::Semaphore> p_RenderFinishedSemaphores,
    std::vector<vk::Fence> p_InFlightFences)
    : m_Device(p_Device), m_GraphicsQueue(p_GraphicsQueue),
      m_PresentQueue(p_PresentQueue), m_SwapChain(p_SwapChain),
      m_CommandBuffers(p_CommandBuffers), m_RenderPass(p_RenderPass),
      m_GraphicsPipeline(p_GraphicsPipeline),
      m_SwapChainExtent(p_SwapChainExtent),
      m_SwapChainFramebuffers(p_SwapChainFramebuffers),
      m_ImageAvailableSemaphores(p_ImageAvailableSemaphores),
      m_RenderFinishedSemaphores(p_RenderFinishedSemaphores),
      m_InFlightFences(p_InFlightFences) {}

void VulkanRenderer::DrawFrame() {
  if(m_Device.waitForFences(1, &m_InFlightFences[m_CurrentFrame], VK_TRUE,
                         UINT64_MAX) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to wait for Fences!");
  }

  uint32_t imageIndex;
  vk::Result result;

  result = m_Device.acquireNextImageKHR(
      m_SwapChain, UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame],
      nullptr, &imageIndex);

  if (result == vk::Result::eErrorOutOfDateKHR) {
    m_ShouldRecreateSwapChain = true;
    return;
  } else if (result != vk::Result::eSuccess &&
             result != vk::Result::eSuboptimalKHR) {
    MYON_DO_CORE_ASSERT("Failed to acquire swap chain image!");
  }

  if(m_Device.resetFences(1, &m_InFlightFences[m_CurrentFrame]) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to reset Fences!");
  }

  m_CommandBuffers[m_CurrentFrame].reset(vk::CommandBufferResetFlags(0));
  recordCommandBuffer(imageIndex);

  vk::SubmitInfo submitInfo{};
  submitInfo.sType = vk::StructureType::eSubmitInfo;

  vk::Semaphore waitSemaphores[] = {m_ImageAvailableSemaphores[m_CurrentFrame]};
  vk::PipelineStageFlags waitStages[] = {
      vk::PipelineStageFlagBits::eColorAttachmentOutput};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &m_CommandBuffers[m_CurrentFrame];

  vk::Semaphore signalSemaphores[] = {
      m_RenderFinishedSemaphores[m_CurrentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if (m_GraphicsQueue.submit(1, &submitInfo,
                             m_InFlightFences[m_CurrentFrame]) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to submit draw command buffer!");
  }

  vk::PresentInfoKHR presentInfo{};
  presentInfo.sType = vk::StructureType::ePresentInfoKHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  vk::SwapchainKHR swapChains[] = {m_SwapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;

  presentInfo.pImageIndices = &imageIndex;

  if(m_PresentQueue.presentKHR(&presentInfo) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to present!");
  }

  m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderer::recordCommandBuffer(uint32_t imageIndex) {
  vk::CommandBufferBeginInfo beginInfo{};
  beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
  beginInfo.flags = vk::CommandBufferUsageFlags(0);
  beginInfo.pInheritanceInfo = nullptr;

  if (m_CommandBuffers[m_CurrentFrame].begin(&beginInfo) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to begin recording command buffer!");
  }

  vk::RenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = vk::StructureType::eRenderPassBeginInfo;
  renderPassInfo.renderPass = m_RenderPass;
  renderPassInfo.framebuffer = m_SwapChainFramebuffers[imageIndex];
  renderPassInfo.renderArea.offset = vk::Offset2D{0, 0};
  renderPassInfo.renderArea.extent = m_SwapChainExtent;

  vk::ClearValue clearColor = {{0.0f, 0.0f, 0.0f, 1.0f}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  m_CommandBuffers[m_CurrentFrame].beginRenderPass(
      &renderPassInfo, vk::SubpassContents::eInline);

  m_CommandBuffers[m_CurrentFrame].bindPipeline(
      vk::PipelineBindPoint::eGraphics, m_GraphicsPipeline);

  vk::Viewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = m_SwapChainExtent.width;
  viewport.height = m_SwapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  m_CommandBuffers[m_CurrentFrame].setViewport(0, 1, &viewport);

  vk::Rect2D scissor{};
  scissor.offset = vk::Offset2D{0, 0};
  scissor.extent = m_SwapChainExtent;
  m_CommandBuffers[m_CurrentFrame].setScissor(0, 1, &scissor);
  m_CommandBuffers[m_CurrentFrame].draw(3, 1, 0, 0);
  m_CommandBuffers[m_CurrentFrame].endRenderPass();

  try {
    m_CommandBuffers[m_CurrentFrame].end();
  } catch (const vk::SystemError &err) {
    MYON_DO_CORE_ASSERT("Failed to record command buffer!");
  }
}


void VulkanRenderer::UpdateSwapchain(vk::Queue p_NewGraphicsQueue,
                       vk::Queue p_NewPresentQueue, vk::SwapchainKHR p_NewSwapChain,
                       std::vector<vk::CommandBuffer> p_NewCommandBuffers,
                       vk::RenderPass p_NewRenderPass,
                       vk::Pipeline p_NewGraphicsPipeline,
                       vk::Extent2D p_NewSwapChainExtent,
                       std::vector<vk::Framebuffer> p_NewSwapChainFramebuffers,
                       std::vector<vk::Semaphore> p_NewImageAvailableSemaphores,
                       std::vector<vk::Semaphore> p_NewRenderFinishedSemaphores,
                       std::vector<vk::Fence> p_NewInFlightFences)
 {
  m_SwapChain = p_NewSwapChain;
  m_GraphicsQueue = p_NewGraphicsQueue;
  m_PresentQueue = p_NewPresentQueue;
  m_RenderPass = p_NewRenderPass;
  m_CommandBuffers = p_NewCommandBuffers;

  m_GraphicsPipeline = p_NewGraphicsPipeline;

  m_SwapChainExtent = p_NewSwapChainExtent;
  m_SwapChainFramebuffers = p_NewSwapChainFramebuffers;

  m_ImageAvailableSemaphores = p_NewImageAvailableSemaphores;
  m_RenderFinishedSemaphores = p_NewRenderFinishedSemaphores;
  m_InFlightFences = p_NewInFlightFences;

  m_CurrentFrame = 0;
}

} // namespace MyonCore

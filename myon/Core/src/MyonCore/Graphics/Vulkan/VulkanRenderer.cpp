#include "MyonCore/Graphics/Vulkan/VulkanRenderer.hpp"

namespace MyonCore {

VulkanRenderer::VulkanRenderer(
    vk::Device p_Device, vk::Queue p_GraphicsQueue, vk::Queue p_PresentQueue,
    vk::SwapchainKHR p_SwapChain, vk::CommandBuffer p_CommandBuffer,
    vk::RenderPass p_RenderPass, vk::Pipeline p_GraphicsPipeline,
    vk::Extent2D p_SwapChainExtent,
    std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
    vk::Semaphore p_ImageAvailableSemaphore,
    vk::Semaphore p_RenderFinishedSemaphore, vk::Fence p_InFlightFence)
    : m_Device(p_Device), m_GraphicsQueue(p_GraphicsQueue),
      m_PresentQueue(p_PresentQueue), m_SwapChain(p_SwapChain),
      m_CommandBuffer(p_CommandBuffer), m_RenderPass(p_RenderPass),
      m_GraphicsPipeline(p_GraphicsPipeline),
      m_SwapChainExtent(p_SwapChainExtent),
      m_SwapChainFramebuffers(p_SwapChainFramebuffers),
      m_ImageAvailableSemaphore(p_ImageAvailableSemaphore),
      m_RenderFinishedSemaphore(p_RenderFinishedSemaphore),
      m_InFlightFence(p_InFlightFence) {}

void VulkanRenderer::DrawFrame() {
  m_Device.waitForFences(1, &m_InFlightFence, VK_TRUE, UINT64_MAX);
  m_Device.resetFences(1, &m_InFlightFence);

  uint32_t imageIndex;
  m_Device.acquireNextImageKHR(m_SwapChain, UINT64_MAX,
                               m_ImageAvailableSemaphore, nullptr, &imageIndex);

  m_CommandBuffer.reset(vk::CommandBufferResetFlags(0));
  recordCommandBuffer(imageIndex);

  vk::SubmitInfo submitInfo{};
  submitInfo.sType = vk::StructureType::eSubmitInfo;

  vk::Semaphore waitSemaphores[] = {m_ImageAvailableSemaphore};
  vk::PipelineStageFlags waitStages[] = {
      vk::PipelineStageFlagBits::eColorAttachmentOutput};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &m_CommandBuffer;

  vk::Semaphore signalSemaphores[] = {m_RenderFinishedSemaphore};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if (m_GraphicsQueue.submit(1, &submitInfo, m_InFlightFence) !=
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

  m_PresentQueue.presentKHR(&presentInfo);
}

void VulkanRenderer::recordCommandBuffer(uint32_t imageIndex) {
  vk::CommandBufferBeginInfo beginInfo{};
  beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
  beginInfo.flags = vk::CommandBufferUsageFlags(0);
  beginInfo.pInheritanceInfo = nullptr;

  if (m_CommandBuffer.begin(&beginInfo) != vk::Result::eSuccess) {
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

  m_CommandBuffer.beginRenderPass(&renderPassInfo,
                                  vk::SubpassContents::eInline);

  m_CommandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics,
                               m_GraphicsPipeline);

  vk::Viewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = m_SwapChainExtent.width;
  viewport.height = m_SwapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  m_CommandBuffer.setViewport(0, 1, &viewport);

  vk::Rect2D scissor{};
  scissor.offset = vk::Offset2D{0, 0};
  scissor.extent = m_SwapChainExtent;
  m_CommandBuffer.setScissor(0, 1, &scissor);
  m_CommandBuffer.draw(3, 1, 0, 0);
  m_CommandBuffer.endRenderPass();

  try {
    m_CommandBuffer.end();
  } catch (const vk::SystemError &err) {
    MYON_DO_CORE_ASSERT("Failed to record command buffer!");
  }

  MYON_CORE_INFO("Successfully recorded command buffer!");
}

} // namespace MyonCore

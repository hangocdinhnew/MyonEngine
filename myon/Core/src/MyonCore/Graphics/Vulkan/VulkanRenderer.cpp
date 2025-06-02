#include "MyonCore/Graphics/Vulkan/VulkanRenderer.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanRenderer::VulkanRenderer(VulkanRendererConfig &p_RendererConfig)
    : m_Device(p_RendererConfig.p_Device),
      m_GraphicsQueue(p_RendererConfig.p_GraphicsQueue),
      m_PresentQueue(p_RendererConfig.p_PresentQueue),
      m_SwapChain(p_RendererConfig.p_SwapChain),
      m_CommandBuffers(p_RendererConfig.p_CommandBuffers),
      m_RenderPass(p_RendererConfig.p_RenderPass),
      m_GraphicsPipeline(p_RendererConfig.p_GraphicsPipeline),
      m_SwapChainExtent(p_RendererConfig.p_SwapChainExtent),
      m_SwapChainFramebuffers(p_RendererConfig.p_SwapChainFramebuffers),
      m_ImageAvailableSemaphores(p_RendererConfig.p_ImageAvailableSemaphores),
      m_RenderFinishedSemaphores(p_RendererConfig.p_RenderFinishedSemaphores),
      m_InFlightFences(p_RendererConfig.p_InFlightFences),
      m_VertexBuffer(p_RendererConfig.p_VertexBuffer),
      m_IndexBuffer(p_RendererConfig.p_IndexBuffer),
      m_UniformBuffersMapped(p_RendererConfig.p_UniformBuffersMapped) {}

void VulkanRenderer::UpdateUniformBuffer() {
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(
                   currentTime - startTime)
                   .count();

  UniformBufferObject ubo{};
  ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f),
                          glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view =
      glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(
      glm::radians(45.0f),
      m_SwapChainExtent.width / (float)m_SwapChainExtent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;

  memcpy(m_UniformBuffersMapped[m_CurrentFrame], &ubo, sizeof(ubo));
}

void VulkanRenderer::DrawFrame() {
  if (m_Device.waitForFences(1, &m_InFlightFences[m_CurrentFrame], VK_TRUE,
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

  if (m_Device.resetFences(1, &m_InFlightFences[m_CurrentFrame]) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to reset Fences!");
  }

  m_CommandBuffers[m_CurrentFrame].reset(vk::CommandBufferResetFlags(0));
  recordCommandBuffer(imageIndex);

  UpdateUniformBuffer();

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

  result = m_PresentQueue.presentKHR(&presentInfo);

  if (result == vk::Result::eErrorOutOfDateKHR ||
      result == vk::Result::eSuboptimalKHR) {
    m_ShouldRecreateSwapChain = true;
  } else if (result != vk::Result::eSuccess) {
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

  vk::Buffer vertexBuffers[] = {m_VertexBuffer};
  vk::DeviceSize offsets[] = {0};
  m_CommandBuffers[m_CurrentFrame].bindVertexBuffers(0, 1, vertexBuffers,
                                                     offsets);

  m_CommandBuffers[m_CurrentFrame].bindIndexBuffer(m_IndexBuffer, 0,
                                                   vk::IndexType::eUint16);

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

  m_CommandBuffers[m_CurrentFrame].drawIndexed(indices.size(), 1, 0, 0, 0);
  m_CommandBuffers[m_CurrentFrame].endRenderPass();

  try {
    m_CommandBuffers[m_CurrentFrame].end();
  } catch (const vk::SystemError &err) {
    MYON_DO_CORE_ASSERT("Failed to record command buffer!");
  }
}

void VulkanRenderer::UpdateSwapchain(VulkanRendererConfig &p_RendererConfig) {
  m_SwapChain = p_RendererConfig.p_SwapChain;
  m_GraphicsQueue = p_RendererConfig.p_GraphicsQueue;
  m_PresentQueue = p_RendererConfig.p_PresentQueue;
  m_RenderPass = p_RendererConfig.p_RenderPass;
  m_CommandBuffers = p_RendererConfig.p_CommandBuffers;

  m_GraphicsPipeline = p_RendererConfig.p_GraphicsPipeline;

  m_SwapChainExtent = p_RendererConfig.p_SwapChainExtent;
  m_SwapChainFramebuffers = p_RendererConfig.p_SwapChainFramebuffers;

  m_ImageAvailableSemaphores = p_RendererConfig.p_ImageAvailableSemaphores;
  m_RenderFinishedSemaphores = p_RendererConfig.p_RenderFinishedSemaphores;
  m_InFlightFences = p_RendererConfig.p_InFlightFences;

  m_CurrentFrame = 0;
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

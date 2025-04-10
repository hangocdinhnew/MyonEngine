#include "MyonCore/Graphics/Vulkan/VulkanCommandBuffers.hpp"

namespace MyonCore {
VulkanCommandBuffer::VulkanCommandBuffer(
    vk::Device p_Device, vk::PhysicalDevice p_PhysicalDevice,
    vk::SurfaceKHR p_Surface, vk::RenderPass p_RenderPass,
    std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
    vk::Extent2D p_SwapChainExtent, vk::Pipeline p_GraphicsPipeline)
    : m_Device(p_Device), m_RenderPass(p_RenderPass),
      m_SwapchainFramebuffers(p_SwapChainFramebuffers),
      m_SwapChainExtent(p_SwapChainExtent),
      m_GraphicsPipeline(p_GraphicsPipeline) {
  QueueFamilyIndices queueFamilyIndices =
      Vulkan_FindQueueFamilies(p_PhysicalDevice, p_Surface);

  vk::CommandPoolCreateInfo poolInfo{};
  poolInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
  poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if (m_Device.createCommandPool(&poolInfo, nullptr, &m_CommandPool) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create command pool!");
  }

  MYON_CORE_INFO("Created a command pool!");

  vk::CommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
  allocInfo.commandPool = m_CommandPool;
  allocInfo.level = vk::CommandBufferLevel::ePrimary;
  allocInfo.commandBufferCount = 1;

  if (m_Device.allocateCommandBuffers(&allocInfo, &m_CommandBuffer) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to allocate Command buffers!");
  }

  MYON_CORE_INFO("Allocated Command buffers!");
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
  MYON_CORE_INFO("Destroying command buffers...");

  m_Device.destroyCommandPool(m_CommandPool, nullptr);
}

void VulkanCommandBuffer::recordCommandBuffer(uint32_t imageIndex) {
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
  renderPassInfo.framebuffer = m_SwapchainFramebuffers[imageIndex];
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
  viewport.width = static_cast<float>(m_SwapChainExtent.width);
  viewport.height = static_cast<float>(m_SwapChainExtent.height);
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

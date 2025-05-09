#include "MyonCore/Graphics/Vulkan/VulkanCommandBuffers.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

namespace MyonCore {
VulkanCommandBuffer::VulkanCommandBuffer(
    VulkanCommandBufferConfig &p_CommandBufferConfig)
    : m_Device(p_CommandBufferConfig.p_Device),
      m_RenderPass(p_CommandBufferConfig.p_RenderPass),
      m_SwapchainFramebuffers(p_CommandBufferConfig.p_SwapChainFramebuffers),
      m_SwapChainExtent(p_CommandBufferConfig.p_SwapChainExtent),
      m_GraphicsPipeline(p_CommandBufferConfig.p_GraphicsPipeline) {
  m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
  QueueFamilyIndices queueFamilyIndices = Vulkan_FindQueueFamilies(
      p_CommandBufferConfig.p_PhysicalDevice, p_CommandBufferConfig.p_Surface);

  vk::CommandPoolCreateInfo poolInfo{};
  poolInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
  poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if (m_Device.createCommandPool(&poolInfo, nullptr, &m_CommandPool) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create command pool!");
  }

  vk::CommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
  allocInfo.commandPool = m_CommandPool;
  allocInfo.level = vk::CommandBufferLevel::ePrimary;
  allocInfo.commandBufferCount = m_CommandBuffers.size();

  if (m_Device.allocateCommandBuffers(&allocInfo, m_CommandBuffers.data()) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to allocate Command buffers!");
  }
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
  m_Device.destroyCommandPool(m_CommandPool, nullptr);
}

void VulkanCommandBuffer::cleanup() {
  m_Device.destroyCommandPool(m_CommandPool, nullptr);
}

} // namespace MyonCore

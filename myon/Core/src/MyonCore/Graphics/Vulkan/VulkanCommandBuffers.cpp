#include "MyonCore/Graphics/Vulkan/VulkanCommandBuffers.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

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
  m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
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
  allocInfo.commandBufferCount = m_CommandBuffers.size();

  if (m_Device.allocateCommandBuffers(&allocInfo, m_CommandBuffers.data()) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to allocate Command buffers!");
  }

  MYON_CORE_INFO("Allocated Command buffers!");
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
  MYON_CORE_INFO("Destroying command buffers...");

  m_Device.destroyCommandPool(m_CommandPool, nullptr);
}

void VulkanCommandBuffer::cleanup() {
  MYON_CORE_INFO("Destroying command buffers...");

  m_Device.destroyCommandPool(m_CommandPool, nullptr);
}

} // namespace MyonCore

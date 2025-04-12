#include "MyonCore/Graphics/Vulkan/VulkanSyncObjects.hpp"

namespace MyonCore {
VulkanSyncObjects::VulkanSyncObjects(vk::Device p_Device) : m_Device(p_Device) {
  vk::SemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = vk::StructureType::eSemaphoreCreateInfo;

  vk::FenceCreateInfo fenceInfo{};
  fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
  fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

  if (m_Device.createSemaphore(&semaphoreInfo, nullptr,
                               &m_ImageAvailableSemaphore) !=
          vk::Result::eSuccess ||
      m_Device.createSemaphore(&semaphoreInfo, nullptr,
                               &m_RenderFinishedSemaphore) !=
          vk::Result::eSuccess ||
      m_Device.createFence(&fenceInfo, nullptr, &m_InFlightFence) !=
          vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create semaphores!");
  }
}

VulkanSyncObjects::~VulkanSyncObjects() {
  m_Device.destroySemaphore(m_ImageAvailableSemaphore, nullptr);
  m_Device.destroySemaphore(m_RenderFinishedSemaphore, nullptr);
  m_Device.destroyFence(m_InFlightFence, nullptr);
}

} // namespace MyonCore

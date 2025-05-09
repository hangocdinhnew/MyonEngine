#include "MyonCore/Graphics/Vulkan/VulkanSyncObjects.hpp"

namespace MyonCore {
VulkanSyncObjects::VulkanSyncObjects(VulkanSyncObjectsConfig& p_SyncObjectsConfig) : m_Device(p_SyncObjectsConfig.p_Device) {
  m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

  vk::SemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = vk::StructureType::eSemaphoreCreateInfo;

  vk::FenceCreateInfo fenceInfo{};
  fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
  fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (m_Device.createSemaphore(&semaphoreInfo, nullptr,
                                 &m_ImageAvailableSemaphores[i]) !=
            vk::Result::eSuccess ||
        m_Device.createSemaphore(&semaphoreInfo, nullptr,
                                 &m_RenderFinishedSemaphores[i]) !=
            vk::Result::eSuccess ||
        m_Device.createFence(&fenceInfo, nullptr, &m_InFlightFences[i]) !=
            vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT(
          "Failed to create synchronization objects for a frame!");
    }
  }
}

VulkanSyncObjects::~VulkanSyncObjects() {
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    m_Device.destroySemaphore(m_ImageAvailableSemaphores[i], nullptr);
    m_Device.destroySemaphore(m_RenderFinishedSemaphores[i], nullptr);
    m_Device.destroyFence(m_InFlightFences[i], nullptr);
  }
}

void VulkanSyncObjects::cleanup() {
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    m_Device.destroySemaphore(m_ImageAvailableSemaphores[i], nullptr);
    m_Device.destroySemaphore(m_RenderFinishedSemaphores[i], nullptr);
    m_Device.destroyFence(m_InFlightFences[i], nullptr);
  }
}

} // namespace MyonCore

#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanSyncObjects {
public:
  VulkanSyncObjects(vk::Device p_Device);
  ~VulkanSyncObjects();

  vk::Semaphore getImageAvailableSemaphore() {
    return m_ImageAvailableSemaphore;
  }

  vk::Semaphore getRenderFinishedSemaphore() {
    return m_RenderFinishedSemaphore;
  }

  vk::Fence getInFlightFence() { return m_InFlightFence; }

private:
  vk::Semaphore m_ImageAvailableSemaphore;
  vk::Semaphore m_RenderFinishedSemaphore;
  vk::Fence m_InFlightFence;

  vk::Device m_Device;
};
} // namespace MyonCore

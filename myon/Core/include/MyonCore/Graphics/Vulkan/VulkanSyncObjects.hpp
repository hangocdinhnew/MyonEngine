#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanSyncObjectsConfig {
  vk::Device p_Device;
};

class VulkanSyncObjects {
public:
  VulkanSyncObjects(VulkanSyncObjectsConfig& p_SyncObjectsConfig);
  ~VulkanSyncObjects();

  std::vector<vk::Semaphore> &getImageAvailableSemaphore() {
    return m_ImageAvailableSemaphores;
  }

  std::vector<vk::Semaphore> &getRenderFinishedSemaphore() {
    return m_RenderFinishedSemaphores;
  }

  std::vector<vk::Fence> &getInFlightFence() { return m_InFlightFences; }

  void cleanup();

private:
  std::vector<vk::Semaphore> m_ImageAvailableSemaphores;
  std::vector<vk::Semaphore> m_RenderFinishedSemaphores;
  std::vector<vk::Fence> m_InFlightFences;

  vk::Device& m_Device;
};
} // namespace MyonCore

#include "MyonCore/Graphics/Vulkan/VulkanDescriptorPool.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanDescriptorPool::VulkanDescriptorPool(
    VulkanDescriptorPoolConfig &p_DescriptorPoolConfig)
    : m_LogicalDevice(p_DescriptorPoolConfig.p_LogicalDevice) {
  vk::DescriptorPoolSize poolSize{};
  poolSize.type = vk::DescriptorType::eUniformBuffer;
  poolSize.descriptorCount = MAX_FRAMES_IN_FLIGHT;

  vk::DescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = &poolSize;
  poolInfo.maxSets = MAX_FRAMES_IN_FLIGHT;

  if (m_LogicalDevice.createDescriptorPool(
          &poolInfo, nullptr, &m_DescriptorPool) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create descriptor pool!");
  }

  MYON_CORE_INFO("Vulkan Descriptor Pool created!");
}

VulkanDescriptorPool::~VulkanDescriptorPool() {
  MYON_CORE_INFO("Destroying Descriptor Pool...");

  m_LogicalDevice.destroyDescriptorPool(m_DescriptorPool, nullptr);
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

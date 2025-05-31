#include "MyonCore/Graphics/Vulkan/VulkanAllocator.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanAllocator::VulkanAllocator(VulkanAllocatorConfig &p_AllocatorConfig) {
  vma::AllocatorCreateInfo allocatorInfo{};
  allocatorInfo.instance = p_AllocatorConfig.p_Instance;
  allocatorInfo.physicalDevice = p_AllocatorConfig.p_PhysicalDevice;
  allocatorInfo.device = p_AllocatorConfig.p_LogicalDevice;

  if (vma::createAllocator(&allocatorInfo, &m_Allocator) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create an VMA allocator!");
  }

  MYON_CORE_INFO("Vulkan Memory Allocator created successfully!");
}

VulkanAllocator::~VulkanAllocator() {
  m_Allocator.destroy();
  MYON_CORE_INFO("Vulkan Memory Allocator destroyed!");
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

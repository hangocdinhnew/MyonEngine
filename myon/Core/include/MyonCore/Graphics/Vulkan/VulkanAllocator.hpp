#pragma once

#include "MyonCore/Core/Log.hpp"
#include <vk_mem_alloc.hpp>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanAllocatorConfig {
  vk::Instance p_Instance;
  vk::PhysicalDevice p_PhysicalDevice;
  vk::Device p_LogicalDevice;
};

class VulkanAllocator {
public:
  VulkanAllocator(VulkanAllocatorConfig &p_AllocatorConfig);
  ~VulkanAllocator();

  vma::Allocator &getAllocator() { return m_Allocator; }

private:
  vma::Allocator m_Allocator;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

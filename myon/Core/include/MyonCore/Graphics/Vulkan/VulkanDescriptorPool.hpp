#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanDescriptorPoolConfig {
  vk::Device p_LogicalDevice;
};

class VulkanDescriptorPool {
public:
  VulkanDescriptorPool(VulkanDescriptorPoolConfig &p_DescriptorPoolConfig);
  ~VulkanDescriptorPool();

  vk::DescriptorPool& getDescriptorPool() { return m_DescriptorPool; }

private:
  vk::Device &m_LogicalDevice;

  vk::DescriptorPool m_DescriptorPool;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanDescriptorSetLayoutConfig {
  vk::Device p_LogicalDevice;
};

class VulkanDescriptorSetLayout {
public:
  VulkanDescriptorSetLayout(
      VulkanDescriptorSetLayoutConfig &p_DescriptorSetLayoutConfig);
  ~VulkanDescriptorSetLayout();

  vk::DescriptorSetLayout getDescriptorSetLayout() {
    return m_DescriptorSetLayout;
  }

private:
  vk::Device m_LogicalDevice;

  vk::DescriptorSetLayout m_DescriptorSetLayout;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

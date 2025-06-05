#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <vulkan/vulkan.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanDescriptorSetsConfig {
  vk::DescriptorSetLayout p_DescriptorSetLayout;
  vk::DescriptorPool p_DescriptorPool;
  vk::Device p_LogicalDevice;
  std::vector<vk::Buffer> p_UniformBuffers;
};

class VulkanDescriptorSets {
public:
  VulkanDescriptorSets(VulkanDescriptorSetsConfig &p_DescriptorSetsConfig);
  ~VulkanDescriptorSets() = default;

  std::vector<vk::DescriptorSet> &getDescriptorSets() {
    return m_DescriptorSets;
  }

private:
  vk::DescriptorSetLayout &m_DescriptorSetLayout;
  vk::DescriptorPool &m_DescriptorPool;
  vk::Device &m_LogicalDevice;
  std::vector<vk::Buffer> &m_UniformBuffers;

  std::vector<vk::DescriptorSet> m_DescriptorSets;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

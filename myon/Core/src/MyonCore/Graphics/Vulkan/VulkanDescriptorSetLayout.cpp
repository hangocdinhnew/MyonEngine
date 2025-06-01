#include "MyonCore/Graphics/Vulkan/VulkanDescriptorSetLayout.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(
    VulkanDescriptorSetLayoutConfig &p_DescriptorSetLayoutConfig)
    : m_LogicalDevice(p_DescriptorSetLayoutConfig.p_LogicalDevice) {
  vk::DescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;
  uboLayoutBinding.pImmutableSamplers = nullptr;

  vk::DescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
  layoutInfo.bindingCount = 1;
  layoutInfo.pBindings = &uboLayoutBinding;

  if (m_LogicalDevice.createDescriptorSetLayout(&layoutInfo, nullptr,
                                                &m_DescriptorSetLayout) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create descriptor set layout!");
  }

  MYON_CORE_INFO("Vulkan Descriptor Set Layout created!");
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout() {
  MYON_CORE_INFO("Destroying Vulkan Descriptor Set Layout...");

  m_LogicalDevice.destroyDescriptorSetLayout(m_DescriptorSetLayout, nullptr);
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

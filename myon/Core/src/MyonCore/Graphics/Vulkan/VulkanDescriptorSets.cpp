// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanDescriptorSets.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanDescriptorSets::VulkanDescriptorSets(
    VulkanDescriptorSetsConfig &p_DescriptorSetsConfig)
    : m_DescriptorSetLayout(p_DescriptorSetsConfig.p_DescriptorSetLayout),
      m_DescriptorPool(p_DescriptorSetsConfig.p_DescriptorPool),
      m_LogicalDevice(p_DescriptorSetsConfig.p_LogicalDevice),
      m_UniformBuffers(p_DescriptorSetsConfig.p_UniformBuffers) {
  std::vector<vk::DescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT,
                                               m_DescriptorSetLayout);
  vk::DescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = vk::StructureType::eDescriptorSetAllocateInfo;
  allocInfo.descriptorPool = m_DescriptorPool;
  allocInfo.descriptorSetCount = MAX_FRAMES_IN_FLIGHT;
  allocInfo.pSetLayouts = layouts.data();

  m_DescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
  if (m_LogicalDevice.allocateDescriptorSets(
          &allocInfo, m_DescriptorSets.data()) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to allocate Descriptor Sets!");
  }

  MYON_CORE_INFO("Descriptor Sets allocated!");

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vk::DescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = m_UniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    vk::WriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
    descriptorWrite.dstSet = m_DescriptorSets[i];
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = vk::DescriptorType::eUniformBuffer;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;
    descriptorWrite.pImageInfo = nullptr;
    descriptorWrite.pTexelBufferView = nullptr;

    m_LogicalDevice.updateDescriptorSets(1, &descriptorWrite, 0, nullptr);
  }
}
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

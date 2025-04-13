#include "MyonCore/Graphics/Vulkan/VulkanVertexBuffer.hpp"

namespace MyonCore {
VulkanVertexBuffer::VulkanVertexBuffer(vk::Device p_LogicalDevice,
                                       vk::PhysicalDevice p_PhysicalDevice)
    : m_LogicalDevice(p_LogicalDevice), m_PhysicalDevice(p_PhysicalDevice) {
  vk::BufferCreateInfo bufferInfo{};
  bufferInfo.sType = vk::StructureType::eBufferCreateInfo;
  bufferInfo.size = sizeof(vertices[0]) * vertices.size();
  bufferInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
  bufferInfo.sharingMode = vk::SharingMode::eExclusive;

  if (m_LogicalDevice.createBuffer(&bufferInfo, nullptr, &m_VertexBuffer) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create Vertex buffer!");
  }

  vk::MemoryRequirements memRequirements;
  m_LogicalDevice.getBufferMemoryRequirements(m_VertexBuffer, &memRequirements);

  vk::MemoryAllocateInfo allocInfo{};
  allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex =
      findMemoryType(memRequirements.memoryTypeBits,
                     vk::MemoryPropertyFlagBits::eHostVisible |
                         vk::MemoryPropertyFlagBits::eHostCoherent);

  if (m_LogicalDevice.allocateMemory(
          &allocInfo, nullptr, &m_VertexBufferMemory) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to allocate vertex buffer memory!");
  }

  m_LogicalDevice.bindBufferMemory(m_VertexBuffer, m_VertexBufferMemory, 0);

  void *data;
  if (m_LogicalDevice.mapMemory(m_VertexBufferMemory, 0, bufferInfo.size,
                                vk::MemoryMapFlags(0),
                                &data) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to map vertex buffer memory!");
  }

  memcpy(data, vertices.data(), bufferInfo.size);

  m_LogicalDevice.unmapMemory(m_VertexBufferMemory);
}

VulkanVertexBuffer::~VulkanVertexBuffer() {
  m_LogicalDevice.destroyBuffer(m_VertexBuffer, nullptr);
  m_LogicalDevice.freeMemory(m_VertexBufferMemory, nullptr);
}

uint32_t
VulkanVertexBuffer::findMemoryType(uint32_t p_TypeFilter,
                                   vk::MemoryPropertyFlags p_Properties) {
  vk::PhysicalDeviceMemoryProperties memProperties;
  m_PhysicalDevice.getMemoryProperties(&memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((p_TypeFilter & (1 << i)) &&
        (memProperties.memoryTypes[i].propertyFlags & p_Properties) ==
            p_Properties) {
      return i;
    }
  }

  MYON_DO_CORE_ASSERT("Failed to find suitable memory type!");
}
} // namespace MyonCore

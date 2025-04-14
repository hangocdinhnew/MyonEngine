#include "MyonCore/Graphics/Vulkan/VulkanVertexBuffer.hpp"

namespace MyonCore {
VulkanVertexBuffer::VulkanVertexBuffer(vk::Device &p_LogicalDevice,
                                       vk::PhysicalDevice &p_PhysicalDevice)
    : m_LogicalDevice(p_LogicalDevice), m_PhysicalDevice(p_PhysicalDevice) {
  vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
  createBuffer(m_LogicalDevice, m_PhysicalDevice, bufferSize,
               vk::BufferUsageFlagBits::eVertexBuffer,
               vk::MemoryPropertyFlagBits::eHostVisible |
                   vk::MemoryPropertyFlagBits::eHostCoherent,
               m_VertexBuffer, m_VertexBufferMemory);

  void *data;
  if (m_LogicalDevice.mapMemory(m_VertexBufferMemory, 0, bufferSize,
                                vk::MemoryMapFlags(0),
                                &data) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to map memory!");
  }
  m_LogicalDevice.unmapMemory(m_VertexBufferMemory);
}

VulkanVertexBuffer::~VulkanVertexBuffer() {
  m_LogicalDevice.destroyBuffer(m_VertexBuffer, nullptr);
  m_LogicalDevice.freeMemory(m_VertexBufferMemory, nullptr);
}

} // namespace MyonCore

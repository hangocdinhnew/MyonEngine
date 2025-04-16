#include "MyonCore/Graphics/Vulkan/VulkanBuffer.hpp"

namespace MyonCore {
VulkanBuffer::VulkanBuffer(vk::Device &p_LogicalDevice,
                           vk::PhysicalDevice &p_PhysicalDevice,
                           vk::CommandPool &p_CommandPool,
                           vk::Queue &p_GraphicsQueue)
    : m_LogicalDevice(p_LogicalDevice), m_PhysicalDevice(p_PhysicalDevice),
      m_CommandPool(p_CommandPool),
      m_GraphicsQueue(p_GraphicsQueue) {
  vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

  vk::Buffer stagingBuffer;
  vk::DeviceMemory stagingBufferMemory;
  createBuffer(m_LogicalDevice, m_PhysicalDevice, bufferSize,
               vk::BufferUsageFlagBits::eTransferSrc,
               vk::MemoryPropertyFlagBits::eHostVisible |
                   vk::MemoryPropertyFlagBits::eHostCoherent,
               stagingBuffer, stagingBufferMemory);

  void *data;
  if (m_LogicalDevice.mapMemory(stagingBufferMemory, 0, bufferSize,
                                vk::MemoryMapFlags(0),
                                &data) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to map memory!");
  }

  memcpy(data, vertices.data(), (size_t)bufferSize);
  m_LogicalDevice.unmapMemory(stagingBufferMemory);

  createBuffer(m_LogicalDevice, m_PhysicalDevice, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eVertexBuffer,
               vk::MemoryPropertyFlagBits::eDeviceLocal, m_VertexBuffer,
               m_VertexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue,
             stagingBuffer, m_VertexBuffer, bufferSize);

  m_LogicalDevice.destroyBuffer(stagingBuffer, nullptr);
  m_LogicalDevice.freeMemory(stagingBufferMemory, nullptr);
}

VulkanBuffer::~VulkanBuffer() {
  m_LogicalDevice.destroyBuffer(m_VertexBuffer, nullptr);
  m_LogicalDevice.freeMemory(m_VertexBufferMemory, nullptr);
}

} // namespace MyonCore

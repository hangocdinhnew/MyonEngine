#include "MyonCore/Graphics/Vulkan/VulkanBuffer.hpp"

namespace MyonCore {
VulkanBuffer::VulkanBuffer(VulkanBufferConfig &p_BufferConfig)
    : m_LogicalDevice(p_BufferConfig.p_LogicalDevice),
      m_PhysicalDevice(p_BufferConfig.p_PhysicalDevice),
      m_CommandPool(p_BufferConfig.p_CommandPool),
      m_GraphicsQueue(p_BufferConfig.p_GraphicsQueue) {
  createVertexBuffer(
      p_BufferConfig.p_LogicalDevice, p_BufferConfig.p_PhysicalDevice,
      p_BufferConfig.p_CommandPool, p_BufferConfig.p_GraphicsQueue);
  createIndexBuffer(
      p_BufferConfig.p_LogicalDevice, p_BufferConfig.p_PhysicalDevice,
      p_BufferConfig.p_CommandPool, p_BufferConfig.p_GraphicsQueue);
}

void VulkanBuffer::createVertexBuffer(vk::Device &p_LogicalDevice,
                                      vk::PhysicalDevice &p_PhysicalDevice,
                                      vk::CommandPool &p_CommandPool,
                                      vk::Queue &p_GraphicsQueue) {
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

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_VertexBuffer, bufferSize);

  m_LogicalDevice.destroyBuffer(stagingBuffer, nullptr);
  m_LogicalDevice.freeMemory(stagingBufferMemory, nullptr);
}

void VulkanBuffer::createIndexBuffer(vk::Device &p_LogicalDevice,
                                     vk::PhysicalDevice &p_PhysicalDevice,
                                     vk::CommandPool &p_CommandPool,
                                     vk::Queue &p_GraphicsQueue) {
  vk::DeviceSize bufferSize = sizeof(indices[0]) * indices.size();

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
  memcpy(data, indices.data(), (size_t)bufferSize);
  m_LogicalDevice.unmapMemory(stagingBufferMemory);

  createBuffer(m_LogicalDevice, m_PhysicalDevice, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eIndexBuffer,
               vk::MemoryPropertyFlagBits::eDeviceLocal, m_IndexBuffer,
               m_IndexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_IndexBuffer, bufferSize);

  m_LogicalDevice.destroyBuffer(stagingBuffer, nullptr);
  m_LogicalDevice.freeMemory(stagingBufferMemory, nullptr);
}

VulkanBuffer::~VulkanBuffer() {
  m_LogicalDevice.destroyBuffer(m_IndexBuffer, nullptr);
  m_LogicalDevice.freeMemory(m_IndexBufferMemory, nullptr);

  m_LogicalDevice.destroyBuffer(m_VertexBuffer, nullptr);
  m_LogicalDevice.freeMemory(m_VertexBufferMemory, nullptr);
}

} // namespace MyonCore

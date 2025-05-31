#include "MyonCore/Graphics/Vulkan/VulkanBuffer.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {

VulkanBuffer::VulkanBuffer(VulkanBufferConfig &p_BufferConfig)
    : m_PhysicalDevice(p_BufferConfig.p_PhysicalDevice),
      m_LogicalDevice(p_BufferConfig.p_LogicalDevice),
      m_CommandPool(p_BufferConfig.p_CommandPool),
      m_GraphicsQueue(p_BufferConfig.p_GraphicsQueue),
      m_MemoryAllocator(p_BufferConfig.p_MemoryAllocator) {
  createVertexBuffer();
  createIndexBuffer();
}

void VulkanBuffer::createVertexBuffer() {
  vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

  vk::Buffer stagingBuffer;
  vma::Allocation stagingBufferMemory;

  createBuffer(
      m_MemoryAllocator, bufferSize, vk::BufferUsageFlagBits::eTransferSrc,
      vma::MemoryUsage::eAutoPreferHost, stagingBuffer, stagingBufferMemory);

  void *data;
  vma::AllocationInfo allocInfo{};
  m_MemoryAllocator.getAllocationInfo(stagingBufferMemory, &allocInfo);
  data = allocInfo.pMappedData;

  if (!data) {
    vmaMapMemory(m_MemoryAllocator, stagingBufferMemory, &data);
  }

  memcpy(data, vertices.data(), (size_t)bufferSize);
  vmaUnmapMemory(m_MemoryAllocator, stagingBufferMemory);

  createBuffer(m_MemoryAllocator, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eVertexBuffer,
               vma::MemoryUsage::eAutoPreferDevice, m_VertexBuffer,
               m_VertexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_VertexBuffer, bufferSize);

  vmaDestroyBuffer(m_MemoryAllocator, stagingBuffer, stagingBufferMemory);
}

void VulkanBuffer::createIndexBuffer() {
  vk::DeviceSize bufferSize = sizeof(indices[0]) * indices.size();

  vk::Buffer stagingBuffer;
  vma::Allocation stagingBufferMemory;

  createBuffer(
      m_MemoryAllocator, bufferSize, vk::BufferUsageFlagBits::eTransferSrc,
      vma::MemoryUsage::eAutoPreferHost, stagingBuffer, stagingBufferMemory);

  void *data;
  vma::AllocationInfo allocInfo{};
  m_MemoryAllocator.getAllocationInfo(stagingBufferMemory, &allocInfo);
  data = allocInfo.pMappedData;

  if (!data) {
    vmaMapMemory(m_MemoryAllocator, stagingBufferMemory, &data);
  }

  memcpy(data, indices.data(), (size_t)bufferSize);
  vmaUnmapMemory(m_MemoryAllocator, stagingBufferMemory);

  createBuffer(m_MemoryAllocator, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eIndexBuffer,
               vma::MemoryUsage::eAutoPreferDevice, m_IndexBuffer,
               m_IndexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_IndexBuffer, bufferSize);

  vmaDestroyBuffer(m_MemoryAllocator, stagingBuffer, stagingBufferMemory);
}

VulkanBuffer::~VulkanBuffer() {
  vmaDestroyBuffer(m_MemoryAllocator, m_IndexBuffer, m_IndexBufferMemory);
  vmaDestroyBuffer(m_MemoryAllocator, m_VertexBuffer, m_VertexBufferMemory);
}

} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

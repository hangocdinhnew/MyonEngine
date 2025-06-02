#include "MyonCore/Graphics/Vulkan/VulkanBuffer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

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
    if (m_MemoryAllocator.mapMemory(stagingBufferMemory, &data) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to map Vertex buffer memory!");
    }
  }

  memcpy(data, vertices.data(), (size_t)bufferSize);
  m_MemoryAllocator.unmapMemory(stagingBufferMemory);

  createBuffer(m_MemoryAllocator, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eVertexBuffer,
               vma::MemoryUsage::eAutoPreferDevice, m_VertexBuffer,
               m_VertexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_VertexBuffer, bufferSize);

  m_MemoryAllocator.destroyBuffer(stagingBuffer, stagingBufferMemory);
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
    if (m_MemoryAllocator.mapMemory(stagingBufferMemory, &data) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to map index buffer memory!");
    }
  }

  memcpy(data, indices.data(), (size_t)bufferSize);
  m_MemoryAllocator.unmapMemory(stagingBufferMemory);

  createBuffer(m_MemoryAllocator, bufferSize,
               vk::BufferUsageFlagBits::eTransferDst |
                   vk::BufferUsageFlagBits::eIndexBuffer,
               vma::MemoryUsage::eAutoPreferDevice, m_IndexBuffer,
               m_IndexBufferMemory);

  copyBuffer(m_LogicalDevice, m_CommandPool, m_GraphicsQueue, stagingBuffer,
             m_IndexBuffer, bufferSize);

  m_MemoryAllocator.destroyBuffer(stagingBuffer, stagingBufferMemory);
}

void VulkanBuffer::createUniformBuffer() {
  vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

  m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
  m_UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
  m_UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    createBuffer(m_MemoryAllocator, bufferSize,
                 vk::BufferUsageFlagBits::eUniformBuffer,
                 vma::MemoryUsage::eAutoPreferHost, m_UniformBuffers[i],
                 m_UniformBuffersMemory[i]);

    vma::AllocationInfo allocInfo{};
    m_MemoryAllocator.getAllocationInfo(m_UniformBuffersMemory[i], &allocInfo);
    m_UniformBuffersMapped[i] = allocInfo.pMappedData;

    if (!m_UniformBuffersMapped[i]) {
      if (m_MemoryAllocator.mapMemory(m_UniformBuffersMemory[i],
                                      &m_UniformBuffersMapped[i]) !=
          vk::Result::eSuccess) {
        MYON_DO_CORE_ASSERT("Failed to map uniform buffer memory!");
      }
    }
  }
}

VulkanBuffer::~VulkanBuffer() {
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    m_MemoryAllocator.destroyBuffer(m_UniformBuffers[i],
                                    m_UniformBuffersMemory[i]);
  }

  m_MemoryAllocator.destroyBuffer(m_IndexBuffer, m_IndexBufferMemory);
  m_MemoryAllocator.destroyBuffer(m_VertexBuffer, m_VertexBufferMemory);
}

} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

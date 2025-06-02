#pragma once

// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.hpp>
#include <cstring>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
struct VulkanBufferConfig {
  vk::Device p_LogicalDevice;
  vk::PhysicalDevice p_PhysicalDevice;
  vk::CommandPool p_CommandPool;
  vk::Queue p_GraphicsQueue;
  vma::Allocator p_MemoryAllocator;
};

class VulkanBuffer {
public:
  VulkanBuffer(VulkanBufferConfig &p_BufferConfig);
  ~VulkanBuffer();

  vk::Buffer &getVertexBuffer() { return m_VertexBuffer; }

  vma::Allocation &getVertexBufferMemory() { return m_VertexBufferMemory; }

  vk::Buffer &getIndexBuffer() { return m_IndexBuffer; }

  vma::Allocation &getIndexBufferMemory() { return m_IndexBufferMemory; }

private:
  vk::Device &m_LogicalDevice;
  vk::PhysicalDevice &m_PhysicalDevice;
  vma::Allocator &m_MemoryAllocator;

  vk::CommandPool &m_CommandPool;
  vk::Queue &m_GraphicsQueue;

  vk::Buffer m_VertexBuffer;
  vma::Allocation m_VertexBufferMemory;

  vk::Buffer m_IndexBuffer;
  vma::Allocation m_IndexBufferMemory;

  std::vector<vk::Buffer> m_UniformBuffers;
  std::vector<vma::Allocation> m_UniformBuffersMemory;
  std::vector<void *> m_UniformBuffersMapped;

  void createVertexBuffer();
  void createIndexBuffer();
  void createUniformBuffer();
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

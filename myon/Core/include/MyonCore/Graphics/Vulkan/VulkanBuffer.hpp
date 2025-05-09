#pragma once

// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>
#include <cstring>
// clang-format on

namespace MyonCore {
struct VulkanBufferConfig {
  vk::Device p_LogicalDevice;
  vk::PhysicalDevice p_PhysicalDevice;
  vk::CommandPool p_CommandPool;
  vk::Queue p_GraphicsQueue;
};

class VulkanBuffer {
public:
  VulkanBuffer(VulkanBufferConfig& p_BufferConfig);
  ~VulkanBuffer();

  vk::Buffer &getVertexBuffer() { return m_VertexBuffer; }

  vk::DeviceMemory &getVertexBufferMemory() { return m_VertexBufferMemory; }

  vk::Buffer &getIndexBuffer() { return m_IndexBuffer; }

  vk::DeviceMemory &getIndexBufferMemory() { return m_IndexBufferMemory; }

private:
  vk::Device &m_LogicalDevice;
  vk::PhysicalDevice &m_PhysicalDevice;

  vk::CommandPool &m_CommandPool;
  vk::Queue &m_GraphicsQueue;

  vk::Buffer m_VertexBuffer;
  vk::DeviceMemory m_VertexBufferMemory;

  vk::Buffer m_IndexBuffer;
  vk::DeviceMemory m_IndexBufferMemory;

  void createVertexBuffer(vk::Device &p_LogicalDevice,
                          vk::PhysicalDevice &p_PhysicalDevice,
                          vk::CommandPool &p_CommandPool,
                          vk::Queue &p_GraphicsQueue);

  void createIndexBuffer(vk::Device &p_LogicalDevice,
                         vk::PhysicalDevice &p_PhysicalDevice,
                         vk::CommandPool &p_CommandPool,
                         vk::Queue &p_GraphicsQueue);
};
} // namespace MyonCore

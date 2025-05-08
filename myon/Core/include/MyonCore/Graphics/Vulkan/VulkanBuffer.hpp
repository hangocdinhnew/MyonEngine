#pragma once

// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>
#include <cstring>
// clang-format on

namespace MyonCore {
class VulkanBuffer {
public:
  VulkanBuffer(vk::Device &p_LogicalDevice,
               vk::PhysicalDevice &p_PhysicalDevice,
               vk::CommandPool &p_CommandPool, vk::Queue &p_GraphicsQueue);
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

  void createVulkanVertexBuffer(vk::Device &p_LogicalDevice,
                                vk::PhysicalDevice &p_PhysicalDevice,
                                vk::CommandPool &p_CommandPool,
                                vk::Queue &p_GraphicsQueue);

  void createVulkanIndexBuffer(vk::Device &p_LogicalDevice,
                               vk::PhysicalDevice &p_PhysicalDevice,
                               vk::CommandPool &p_CommandPool,
                               vk::Queue &p_GraphicsQueue);
};
} // namespace MyonCore

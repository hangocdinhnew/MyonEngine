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
                     vk::PhysicalDevice &p_PhysicalDevice);
  ~VulkanBuffer();

  vk::Buffer& getVertexBuffer() { return m_VertexBuffer; }

  vk::DeviceMemory& getVertexBufferMemory() { return m_VertexBufferMemory; }

private:
  vk::Device& m_LogicalDevice;
  vk::PhysicalDevice& m_PhysicalDevice;

  vk::Buffer m_VertexBuffer;
  vk::DeviceMemory m_VertexBufferMemory;
};
} // namespace MyonCore

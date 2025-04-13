#pragma once

// clang-format off
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>
#include <cstring>
// clang-format on

namespace MyonCore {
class VulkanVertexBuffer {
public:
  VulkanVertexBuffer(vk::Device &p_LogicalDevice,
                     vk::PhysicalDevice &p_PhysicalDevice);
  ~VulkanVertexBuffer();

  vk::Buffer& getVertexBuffer() { return m_VertexBuffer; }

  vk::DeviceMemory& getVertexBufferMemory() { return m_VertexBufferMemory; }

private:
  vk::Device& m_LogicalDevice;
  vk::PhysicalDevice& m_PhysicalDevice;

  vk::Buffer m_VertexBuffer;
  vk::DeviceMemory m_VertexBufferMemory;

  uint32_t findMemoryType(uint32_t p_TypeFilter,
                          vk::MemoryPropertyFlags p_Properties);
};
} // namespace MyonCore

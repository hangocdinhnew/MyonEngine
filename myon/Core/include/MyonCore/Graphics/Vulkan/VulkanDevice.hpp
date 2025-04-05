#pragma once
#include <MyonCore/Core/Log.hpp>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() { return graphicsFamily.has_value(); }
};

class VulkanDevice {
public:
  VulkanDevice(vk::Instance &p_Instance);
  ~VulkanDevice();

private:
  bool isDeviceSuitable(vk::PhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);

  vk::Device m_Device;
  vk::Queue m_GraphicsQueue;
};

} // namespace MyonCore

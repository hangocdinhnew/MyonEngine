#pragma once
#include <MyonBackend/Core/Log.hpp>
#include <vulkan/vulkan.hpp>

namespace MyonBackend {
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() { return graphicsFamily.has_value(); }
};

class VulkanPhysicalDevice {
public:
  VulkanPhysicalDevice(vk::Instance &p_Instance);
  ~VulkanPhysicalDevice();

private:
  bool isDeviceSuitable(vk::PhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);
};

} // namespace MyonBackend

#pragma once
#include <MyonCore/Core/Log.hpp>
#include <vulkan/vulkan.hpp>
#include <set>

namespace MyonCore {
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

class VulkanDevice {
public:
  VulkanDevice(vk::Instance &p_Instance, vk::SurfaceKHR p_Surface);
  ~VulkanDevice();

private:
  bool isDeviceSuitable(vk::PhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);

  vk::Device m_Device;
  vk::Queue m_GraphicsQueue;
  vk::Queue m_PresentQueue;
  vk::SurfaceKHR m_Surface;
};

} // namespace MyonCore

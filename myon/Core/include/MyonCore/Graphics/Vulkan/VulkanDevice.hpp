#pragma once
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanStructs.hpp"
#include <set>
#include <vulkan/vulkan.hpp>

namespace MyonCore {
class VulkanDevice {
public:
  VulkanDevice(vk::Instance &p_Instance, vk::SurfaceKHR p_Surface);
  ~VulkanDevice();

  vk::PhysicalDevice& getPhysicalDevice() { return m_PhysicalDevice; };
  vk::Device& getLogicalDevice() { return m_Device; }

private:
  bool isDeviceSuitable(vk::PhysicalDevice device);
  bool checkDeviceExtensionSupport(vk::PhysicalDevice device);

  vk::PhysicalDevice m_PhysicalDevice = nullptr;
  vk::Device m_Device;
  vk::Queue m_GraphicsQueue;
  vk::Queue m_PresentQueue;
  vk::SurfaceKHR m_Surface;
};

} // namespace MyonCore

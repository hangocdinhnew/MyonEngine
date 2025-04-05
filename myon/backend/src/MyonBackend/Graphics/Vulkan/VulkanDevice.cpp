#include "MyonBackend/Graphics/Vulkan/VulkanCfg.hpp"
#include <MyonBackend/Graphics/Vulkan/VulkanDevice.hpp>

namespace MyonBackend {
VulkanDevice::VulkanDevice(vk::Instance &p_Instance) {
  vk::PhysicalDevice physicalDevice = nullptr;

  uint32_t deviceCount = 0;
  p_Instance.enumeratePhysicalDevices(&deviceCount, nullptr);

  if (deviceCount == 0) {
    MYON_DO_CORE_ASSERT("Failed to find GPUs with Vulkan support!");
  }

  std::vector<vk::PhysicalDevice> devices(deviceCount);
  p_Instance.enumeratePhysicalDevices(&deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device)) {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == nullptr) {
    MYON_DO_CORE_ASSERT("Failed to find a suitable GPU!");
  }

  MYON_CORE_INFO("Vulkan Physicial Devices picked!");

  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  vk::DeviceQueueCreateInfo queueCreateInfo{};
  queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
  queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;

  float queuePriority = 1.0f;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  vk::PhysicalDeviceFeatures deviceFeatures{};

  vk::DeviceCreateInfo createInfo{};
  createInfo.sType = vk::StructureType::eDeviceCreateInfo;

  createInfo.pQueueCreateInfos = &queueCreateInfo;
  createInfo.queueCreateInfoCount = 1;

  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount = 0;

  if (enableValidationLayers) {
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  if (physicalDevice.createDevice(&createInfo, nullptr, &m_Device) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to create Logical device!");
  }

  m_Device.getQueue(indices.graphicsFamily.value(), 0, &m_GraphicsQueue);

  MYON_CORE_INFO("Initialized logical devices.");
}

VulkanDevice::~VulkanDevice() {
  m_Device.destroy(nullptr);

  MYON_CORE_INFO("Unpicking device...");
}

bool VulkanDevice::isDeviceSuitable(vk::PhysicalDevice device) {
  QueueFamilyIndices indices = findQueueFamilies(device);

  return indices.isComplete();
}

QueueFamilyIndices VulkanDevice::findQueueFamilies(vk::PhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  device.getQueueFamilyProperties(&queueFamilyCount, nullptr);

  std::vector<vk::QueueFamilyProperties> queueFamilies(queueFamilyCount);
  device.getQueueFamilyProperties(&queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto &queueFamily : queueFamilies) {
    if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
      indices.graphicsFamily = i;
    }

    if (indices.isComplete()) {
      break;
    }

    i++;
  }

  return indices;
}

} // namespace MyonBackend

#include "MyonCore/Graphics/Vulkan/VulkanDevice.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanCfg.hpp"
#include "vulkan/vulkan_enums.hpp"

namespace MyonCore {
VulkanDevice::VulkanDevice(vk::Instance &p_Instance, vk::SurfaceKHR p_Surface)
    : m_Surface(p_Surface) {
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

  std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(),
                                            indices.presentFamily.value()};

  float queuePriority = 1.0f;
  for (uint32_t queueFamily : uniqueQueueFamilies) {
    vk::DeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  vk::PhysicalDeviceFeatures deviceFeatures{};

  vk::DeviceCreateInfo createInfo{};
  createInfo.sType = vk::StructureType::eDeviceCreateInfo;

  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = queueCreateInfos.size();

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
  m_Device.getQueue(indices.presentFamily.value(), 0, &m_PresentQueue);

  MYON_CORE_INFO("Initialized logical devices.");
}

VulkanDevice::~VulkanDevice() {
  MYON_CORE_INFO("Destroying device...");

  m_Device.destroy(nullptr);
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

    vk::Bool32 presentSupport = false;
    device.getSurfaceSupportKHR(i, m_Surface, &presentSupport);

    if (presentSupport) {
      indices.presentFamily = i;
    }

    if (indices.isComplete()) {
      break;
    }

    i++;
  }

  return indices;
}

} // namespace MyonCore

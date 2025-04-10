#include "MyonCore/Graphics/Vulkan/VulkanDevice.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"

namespace MyonCore {
VulkanDevice::VulkanDevice(vk::Instance &p_Instance, vk::SurfaceKHR p_Surface)
    : m_Surface(p_Surface) {

  uint32_t deviceCount = 0;
  p_Instance.enumeratePhysicalDevices(&deviceCount, nullptr);

  if (deviceCount == 0) {
    MYON_DO_CORE_ASSERT("Failed to find GPUs with Vulkan support!");
  }

  std::vector<vk::PhysicalDevice> devices(deviceCount);
  p_Instance.enumeratePhysicalDevices(&deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device)) {
      m_PhysicalDevice = device;
      break;
    }
  }

  if (m_PhysicalDevice == nullptr) {
    MYON_DO_CORE_ASSERT("Failed to find a suitable GPU!");
  }

  MYON_CORE_INFO("Vulkan Physicial Devices picked!");

  QueueFamilyIndices indices = Vulkan_FindQueueFamilies(m_PhysicalDevice, m_Surface);

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

  createInfo.enabledExtensionCount = deviceExtensions.size();
  createInfo.ppEnabledExtensionNames = deviceExtensions.data();

  if (enableValidationLayers) {
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  if (m_PhysicalDevice.createDevice(&createInfo, nullptr, &m_Device) !=
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
  QueueFamilyIndices indices = Vulkan_FindQueueFamilies(device, m_Surface);

  bool extensionsSupported = checkDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported) {
    SwapChainSupportDetails swapChainSupport = Vulkan_QuerySwapChainSupport(device, m_Surface);
    swapChainAdequate = !swapChainSupport.formats.empty() &&
                        !swapChainSupport.presentModes.empty();
  }

  return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool VulkanDevice::checkDeviceExtensionSupport(vk::PhysicalDevice device) {
  uint32_t extensionCount;
  device.enumerateDeviceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
  device.enumerateDeviceExtensionProperties(nullptr, &extensionCount,
                                            availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceExtensions.begin(),
                                           deviceExtensions.end());

  for (const auto &extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}
} // namespace MyonCore

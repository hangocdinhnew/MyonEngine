#include <MyonBackend/Graphics/Vulkan/VulkanPhysicalDevice.hpp>

namespace MyonBackend {
VulkanPhysicalDevice::VulkanPhysicalDevice(vk::Instance &p_Instance) {
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
}

VulkanPhysicalDevice::~VulkanPhysicalDevice() {
  MYON_CORE_INFO("Unpicking device...");
}

bool VulkanPhysicalDevice::isDeviceSuitable(vk::PhysicalDevice device) {
  QueueFamilyIndices indices = findQueueFamilies(device);

  return indices.isComplete();
}

QueueFamilyIndices
VulkanPhysicalDevice::findQueueFamilies(vk::PhysicalDevice device) {
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

// CONFIG FILE
#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>

// FIXME: This thing is terrible, TERRIBLE.

#ifdef MYON_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef __APPLE__
const std::vector<const char *> deviceExtensions = {
    vk::KHRSwapchainExtensionName, "VK_KHR_portability_subset"};
#else
const std::vector<const char *> deviceExtensions = {
    vk::KHRSwapchainExtensionName};
#endif

namespace MyonCore {

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  vk::SurfaceCapabilitiesKHR capabilities;
  std::vector<vk::SurfaceFormatKHR> formats;
  std::vector<vk::PresentModeKHR> presentModes;
};

inline QueueFamilyIndices Vulkan_FindQueueFamilies(vk::PhysicalDevice device,
                                                   vk::SurfaceKHR surface) {
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
    device.getSurfaceSupportKHR(i, surface, &presentSupport);

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

inline SwapChainSupportDetails
Vulkan_QuerySwapChainSupport(vk::PhysicalDevice device,
                             vk::SurfaceKHR surface) {
  SwapChainSupportDetails details;

  device.getSurfaceCapabilitiesKHR(surface, &details.capabilities);

  uint32_t formatCount;
  device.getSurfaceFormatsKHR(surface, &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    device.getSurfaceFormatsKHR(surface, &formatCount, details.formats.data());
  }

  uint32_t presentModeCount;
  device.getSurfacePresentModesKHR(surface, &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    device.getSurfacePresentModesKHR(surface, &presentModeCount,
                                     details.presentModes.data());
  }

  return details;
}
} // namespace MyonCore

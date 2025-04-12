// CONFIG FILE
#pragma once
#include "MyonCore/Core/Log.hpp"
#include <vector>
#include <vulkan/vulkan.hpp>

// FIXME: This file is terrible, TERRIBLE.

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

const int MAX_FRAMES_IN_FLIGHT = 2;

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
    if (device.getSurfaceSupportKHR(i, surface, &presentSupport) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to get Surface support.");
    }

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

  if (device.getSurfaceCapabilitiesKHR(surface, &details.capabilities) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to get surface capabilities!");
  }

  uint32_t formatCount;
  if (device.getSurfaceFormatsKHR(surface, &formatCount, nullptr) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to get surface formats!");
  }

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    if (device.getSurfaceFormatsKHR(surface, &formatCount,
                                    details.formats.data()) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to get surface formats!");
    }
  }

  uint32_t presentModeCount;
  if(device.getSurfacePresentModesKHR(surface, &presentModeCount, nullptr) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to get Surface Present Modes!");
  }

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    if(device.getSurfacePresentModesKHR(surface, &presentModeCount,
                                     details.presentModes.data()) != vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to get Surface Present Modes!");
    }
  }

  return details;
}
} // namespace MyonCore

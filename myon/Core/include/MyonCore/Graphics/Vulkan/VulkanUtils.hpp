// CONFIG FILE
#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <vector>
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>
// clang-format on

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
  if (device.getSurfacePresentModesKHR(surface, &presentModeCount, nullptr) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to get Surface Present Modes!");
  }

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    if (device.getSurfacePresentModesKHR(surface, &presentModeCount,
                                         details.presentModes.data()) !=
        vk::Result::eSuccess) {
      MYON_DO_CORE_ASSERT("Failed to get Surface Present Modes!");
    }
  }

  return details;
}

struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static vk::VertexInputBindingDescription getBindingDescription() {
    vk::VertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = vk::VertexInputRate::eVertex;

    return bindingDescription;
  }

  static std::array<vk::VertexInputAttributeDescription, 2>
  getAttributeDescriptions() {
    std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions{};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = vk::Format::eR32G32Sfloat;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    return attributeDescriptions;
  }
};

const std::vector<Vertex> vertices = {{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                      {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
                                      {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
} // namespace MyonCore

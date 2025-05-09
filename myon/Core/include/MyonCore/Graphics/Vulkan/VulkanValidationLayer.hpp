#pragma once
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanUtils.hpp"
#include <vulkan/vulkan.hpp>

namespace MyonCore {
struct VulkanValidationLayerConfig {
  vk::Instance p_Instance;
};

class VulkanValidationLayer {
public:
  VulkanValidationLayer(VulkanValidationLayerConfig& p_ValidationLayerConfig);
  ~VulkanValidationLayer();

  vk::Result CreateDebugUtilsMessengerEXT(
      vk::Instance instance,
      const vk::DebugUtilsMessengerCreateInfoEXT *pCreateInfo,
      const vk::AllocationCallbacks *pAllocator,
      vk::DebugUtilsMessengerEXT *pDebugMessenger);
  void DestroyDebugUtilsMessengerEXT(vk::Instance &p_Instance,
                                     vk::DebugUtilsMessengerEXT debugMessenger,
                                     const vk::AllocationCallbacks *pAllocator);

  void populateDebugMessengerCreateInfo(
      vk::DebugUtilsMessengerCreateInfoEXT &createInfo);

private:
  vk::DebugUtilsMessengerEXT m_DebugMessenger;
  vk::Instance& m_Instance;
};
} // namespace MyonCore

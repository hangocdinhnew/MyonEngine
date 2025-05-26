#include "MyonCore/Graphics/Vulkan/VulkanValidationLayer.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              vk::DebugUtilsMessageTypeFlagsEXT messageType,
              const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
              void *pUserData) {
  MYON_ERROR("Message from Validation Layers - {}", pCallbackData->pMessage);

  return vk::False;
}

VulkanValidationLayer::VulkanValidationLayer(
    VulkanValidationLayerConfig &p_ValidationLayerConfig)
    : m_Instance(p_ValidationLayerConfig.p_Instance) {
  if (!enableValidationLayers)
    return;

  vk::DebugUtilsMessengerCreateInfoEXT createInfo;
  populateDebugMessengerCreateInfo(createInfo);

  if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr,
                                   &m_DebugMessenger) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to set up debug messenger!");
  }

  MYON_CORE_INFO("Setting up debug messager using Vulkan Validation Layers has "
                 "completed!");
}

void VulkanValidationLayer::populateDebugMessengerCreateInfo(
    vk::DebugUtilsMessengerCreateInfoEXT &createInfo) {
  createInfo = vk::DebugUtilsMessengerCreateInfoEXT{};
  createInfo.sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
  createInfo.messageSeverity =
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
  createInfo.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                           vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                           vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
  createInfo.pfnUserCallback = debugCallback;
}

vk::Result VulkanValidationLayer::CreateDebugUtilsMessengerEXT(
    vk::Instance instance,
    const vk::DebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const vk::AllocationCallbacks *pAllocator,
    vk::DebugUtilsMessengerEXT *pDebugMessenger) {
  auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
      instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));

  if (!func) {
    MYON_CORE_ERROR("Failed to load vkCreateDebugUtilsMessengerEXT");
    return vk::Result::eErrorExtensionNotPresent;
  }

  VkResult result = func(
      instance,
      reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT *>(pCreateInfo),
      reinterpret_cast<const VkAllocationCallbacks *>(pAllocator),
      reinterpret_cast<VkDebugUtilsMessengerEXT *>(pDebugMessenger));

  return static_cast<vk::Result>(result);
}

void VulkanValidationLayer::DestroyDebugUtilsMessengerEXT(
    vk::Instance &p_Instance, vk::DebugUtilsMessengerEXT debugMessenger,
    const vk::AllocationCallbacks *pAllocator) {

  auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
      p_Instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));

  if (!func) {
    MYON_CORE_ERROR("Failed to load vkDestroyDebugUtilsMessengerEXT");
    return;
  }

  func(static_cast<VkInstance>(p_Instance),
       static_cast<VkDebugUtilsMessengerEXT>(debugMessenger),
       reinterpret_cast<const VkAllocationCallbacks *>(pAllocator));
}

VulkanValidationLayer::~VulkanValidationLayer() {
  MYON_CORE_INFO("Shutting down Validation Layer...");

  if (enableValidationLayers) {
    DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
  }
}

} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

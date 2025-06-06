#include "MyonCore/Graphics/Vulkan/VulkanInstance.hpp"

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
VulkanInstance::VulkanInstance(VulkanInstanceConfig &p_InstanceConfig) {
  // Step 1: Vulkan App Info
  vk::ApplicationInfo appInfo{};
  appInfo.sType = vk::StructureType::eApplicationInfo;
  appInfo.pApplicationName = p_InstanceConfig.title.c_str();
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "Myon Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = vk::ApiVersion14;

  // Step 2: Get required extensions from sdl
  auto extensions = getRequiredExtensions();

  // Step 3: Get Vulkan-supported extensions
  uint32_t extensionCount = 0;
  if (vk::enumerateInstanceExtensionProperties(
          nullptr, &extensionCount, nullptr) != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to enumerate instance extension properties!");
  }

  std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
  if (vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                               availableExtensions.data()) !=
      vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("Failed to enumerate instance extension properties!");
  }

  // Step 4: Validate required extensions against available ones
  std::set<std::string> availableExtensionsSet;
  for (const auto &ext : availableExtensions) {
    availableExtensionsSet.insert(ext.extensionName);
  }

  MYON_CORE_INFO("Available Vulkan Extensions:");
  for (const auto &ext : availableExtensionsSet) {
    MYON_CORE_INFO("\t{}", ext);
  }

  for (const char *requiredExt : extensions) {
    if (availableExtensionsSet.find(requiredExt) ==
        availableExtensionsSet.end()) {
      MYON_DO_CORE_ASSERT("Required Vulkan extension '{}' is NOT supported!",
                          requiredExt);
    }
  }

  MYON_CORE_INFO("All required Vulkan extensions are supported!");

  // Step 5: Create Vulkan instance
  vk::InstanceCreateInfo createInfo{};
  createInfo.sType = vk::StructureType::eInstanceCreateInfo;
  createInfo.pApplicationInfo = &appInfo;
  if (enableValidationLayers) {
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  createInfo.ppEnabledExtensionNames = extensions.data();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());

#ifdef __APPLE__
  createInfo.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
#endif

  if (enableValidationLayers && !checkValidationLayerSupport()) {
    MYON_DO_CORE_ASSERT("Validation layers requested, but not available!");
  }

  vk::Result result = vk::createInstance(&createInfo, nullptr, &m_Instance);
  if (result != vk::Result::eSuccess) {
    MYON_DO_CORE_ASSERT("vkCreateInstance failed with error: {}",
                        vk::to_string(result));
  }

  MYON_CORE_INFO("Vulkan instance created successfully!");
}

VulkanInstance::~VulkanInstance() {
  MYON_CORE_INFO("Shutting down Vulkan instance...");

  m_Instance.destroy(nullptr);
}

std::vector<const char *> VulkanInstance::getRequiredExtensions() {
  uint32_t sdlExtensionCount = 0;
  const char *const *sdlExtensions;
  sdlExtensions = SDL_Vulkan_GetInstanceExtensions(&sdlExtensionCount);

  std::vector<const char *> extensions(sdlExtensions,
                                       sdlExtensions + sdlExtensionCount);

  if (enableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return extensions;
}

bool VulkanInstance::checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char *layerName : validationLayers) {
    bool layerFound = false;

    for (const auto &layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

#include "MyonBackend/Graphics/VulkanInstance.hpp"

namespace MyonBackend {
VulkanInstance::VulkanInstance(const std::string &title) {
  // Step 1: Vulkan App Info
  vk::ApplicationInfo appInfo{};
  appInfo.sType = vk::StructureType::eApplicationInfo;
  appInfo.pApplicationName = title.c_str();
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "Myon Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_3;

  // Step 2: Get required extensions from GLFW
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions =
      glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char *> extensions_list(
      glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef __APPLE__
  extensions_list.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

  // Step 3: Get Vulkan-supported extensions
  uint32_t extensionCount = 0;
  vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
  vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           availableExtensions.data());

  // Step 4: Validate required extensions against available ones
  std::set<std::string> availableExtensionsSet;
  for (const auto &ext : availableExtensions) {
    availableExtensionsSet.insert(ext.extensionName);
  }

  MYON_CORE_INFO("Available Vulkan Extensions:");
  for (const auto &ext : availableExtensionsSet) {
    MYON_CORE_INFO("\t{}", ext);
  }

  for (const char *requiredExt : extensions_list) {
    if (availableExtensionsSet.find(requiredExt) ==
        availableExtensionsSet.end()) {
      MYON_CORE_ERROR("Required Vulkan extension '{}' is NOT supported!",
                      requiredExt);
      std::terminate();
    }
  }

  MYON_CORE_INFO("All required Vulkan extensions are supported!");

  // Step 5: Create Vulkan instance
  vk::InstanceCreateInfo createInfo{};
  createInfo.sType = vk::StructureType::eInstanceCreateInfo;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.ppEnabledExtensionNames = extensions_list.data();
  createInfo.enabledExtensionCount =
      static_cast<uint32_t>(extensions_list.size());

#ifdef __APPLE__
  createInfo.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
#endif

  if (vk::createInstance(&createInfo, nullptr, &instance) !=
      vk::Result::eSuccess) {
    MYON_CORE_ERROR("Failed to create Vulkan instance!");
    std::terminate();
  }

  MYON_CORE_INFO("Vulkan instance created successfully!");
}

VulkanInstance::~VulkanInstance() {
  MYON_CORE_INFO("Shutting down Vulkan instance...");
  instance.destroy(nullptr);
}

} // namespace MyonBackend

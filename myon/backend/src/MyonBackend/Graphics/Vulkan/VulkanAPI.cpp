#include "MyonBackend/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonBackend {
VulkanAPI::VulkanAPI(const std::string &title) {
  m_Instance = new VulkanInstance(title);
  m_ValidationLayer = new VulkanValidationLayer(m_Instance->getInstance());
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() {
  MYON_CORE_INFO("Shutting down Vulkan...");
  delete m_ValidationLayer;
  delete m_Instance;
}
}

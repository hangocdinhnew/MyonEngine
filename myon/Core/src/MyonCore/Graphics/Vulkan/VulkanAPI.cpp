#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
VulkanAPI::VulkanAPI(SDL_Window* p_Window, const std::string &title) {
  m_Instance = std::make_unique<VulkanInstance>(title);
  m_ValidationLayer = std::make_unique<VulkanValidationLayer>(m_Instance->getInstance());
  m_VulkanSurface = std::make_unique<VulkanSurface>(p_Window, m_Instance->getInstance());
  m_VulkanDevice = std::make_unique<VulkanDevice>(m_Instance->getInstance(), m_VulkanSurface->GetSurface());
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() {
  MYON_CORE_INFO("Shutting down Vulkan...");
}
}

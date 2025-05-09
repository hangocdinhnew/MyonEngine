#include "MyonCore/Graphics/Vulkan/VulkanSurface.hpp"

namespace MyonCore {
VulkanSurface::VulkanSurface(VulkanSurfaceConfig& p_SurfaceConfig)
    : m_Window(p_SurfaceConfig.p_Window), m_Instance(p_SurfaceConfig.p_Instance) {
  if (!SDL_Vulkan_CreateSurface(m_Window, m_Instance, nullptr,
                                (VkSurfaceKHR *)&m_Surface))
    MYON_DO_CORE_ASSERT("Failed to create a Vulkan Surface!");

  MYON_CORE_INFO("Vulkan Surface has been created!");
}

VulkanSurface::~VulkanSurface() {
  MYON_CORE_INFO("Destroying Vulkan Surface...");
  vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
}

} // namespace MyonCore

#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

/*
vk::Device p_Device,
                                   std::vector<vk::Image> p_SwapChainImages,
                                   vk::Format p_SwapChainImageFormat
*/

namespace MyonCore {
VulkanAPI::VulkanAPI(SDL_Window *p_Window, const std::string &title) {
  m_VulkanInstance = std::make_unique<VulkanInstance>(title);
  m_VulkanValidationLayer =
      std::make_unique<VulkanValidationLayer>(m_VulkanInstance->getInstance());
  m_VulkanSurface = std::make_unique<VulkanSurface>(
      p_Window, m_VulkanInstance->getInstance());
  m_VulkanDevice = std::make_unique<VulkanDevice>(
      m_VulkanInstance->getInstance(), m_VulkanSurface->getSurface());
  m_VulkanSwapchain = std::make_unique<VulkanSwapChain>(
      p_Window, m_VulkanDevice->getPhysicalDevice(),
      m_VulkanDevice->getLogicalDevice(), m_VulkanSurface->getSurface());
  m_VulkanImageViews = std::make_unique<VulkanImageViews>(
      m_VulkanDevice->getLogicalDevice(),
      m_VulkanSwapchain->getSwapChainImages(),
      m_VulkanSwapchain->getSwapChainImageFormat());
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() { MYON_CORE_INFO("Shutting down Vulkan..."); }
} // namespace MyonCore

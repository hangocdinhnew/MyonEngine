#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
VulkanAPI::VulkanAPI(SDL_Window *p_Window, const std::string &title,
                     const std::string vert, const std::string frag) {
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
  m_VulkanGraphicsPipeline = std::make_unique<VulkanGraphicsPipeline>(
      m_VulkanDevice->getLogicalDevice(), vert, frag);
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() { MYON_CORE_INFO("Shutting down Vulkan..."); }
} // namespace MyonCore

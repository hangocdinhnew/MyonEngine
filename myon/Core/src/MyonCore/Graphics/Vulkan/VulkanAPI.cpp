#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

/*
 vk::Device p_Device, vk::PhysicalDevice p_PhysiaclDevice,
    vk::SurfaceKHR p_Surface, vk::RenderPass p_RenderPass,
    std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
    vk::Extent2D p_SwapChainExtent, vk::Pipeline p_GraphicsPipeline
  */

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
  m_VulkanRenderPass = std::make_unique<VulkanRenderPass>(
      m_VulkanDevice->getLogicalDevice(),
      m_VulkanSwapchain->getSwapChainImageFormat());
  m_VulkanGraphicsPipeline = std::make_unique<VulkanGraphicsPipeline>(
      m_VulkanDevice->getLogicalDevice(), m_VulkanRenderPass->getRenderPass(),
      vert, frag);
  m_VulkanFramebuffer = std::make_unique<VulkanFramebuffer>(
      m_VulkanDevice->getLogicalDevice(), m_VulkanRenderPass->getRenderPass(),
      m_VulkanImageViews->getSwapChainImageViews(),
      m_VulkanSwapchain->getSwapChainExtent());
  m_VulkanCommandBuffers = std::make_unique<VulkanCommandBuffer>(
      m_VulkanDevice->getLogicalDevice(), m_VulkanDevice->getPhysicalDevice(),
      m_VulkanSurface->getSurface(), m_VulkanRenderPass->getRenderPass(),
      m_VulkanFramebuffer->getSwapchainFramebuffers(),
      m_VulkanSwapchain->getSwapChainExtent(),
      m_VulkanGraphicsPipeline->getGraphicsPipeline());
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() { MYON_CORE_INFO("Shutting down Vulkan..."); }
} // namespace MyonCore

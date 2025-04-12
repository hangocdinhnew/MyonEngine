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
  m_VulkanSyncObjects =
      std::make_unique<VulkanSyncObjects>(m_VulkanDevice->getLogicalDevice());
  m_VulkanRenderer = std::make_unique<VulkanRenderer>(
      m_VulkanDevice->getLogicalDevice(), m_VulkanDevice->getGraphicsQueue(),
      m_VulkanDevice->getPresentQueue(), m_VulkanSwapchain->getSwapChain(),
      m_VulkanCommandBuffers->getCommandBuffer(),
      m_VulkanRenderPass->getRenderPass(),
      m_VulkanGraphicsPipeline->getGraphicsPipeline(),
      m_VulkanSwapchain->getSwapChainExtent(),
      m_VulkanFramebuffer->getSwapchainFramebuffers(),
      m_VulkanSyncObjects->getImageAvailableSemaphore(),
      m_VulkanSyncObjects->getRenderFinishedSemaphore(),
      m_VulkanSyncObjects->getInFlightFence());
  MYON_CORE_INFO("Initialized Vulkan!");
}

VulkanAPI::~VulkanAPI() { MYON_CORE_INFO("Shutting down Vulkan..."); }

/*
vk::Device p_Device, vk::Queue p_GraphicsQueue, vk::Queue p_PresentQueue,
    vk::SwapchainKHR p_SwapChain, vk::CommandBuffer p_CommandBuffer,
    vk::RenderPass p_RenderPass, vk::Pipeline p_GraphicsPipeline,
    vk::Extent2D p_SwapChainExtent,
    std::vector<vk::Framebuffer> p_SwapChainFramebuffers,
    vk::Semaphore p_ImageAvailableSemaphore,
    vk::Semaphore p_RenderFinishedSemaphore, vk::Fence p_InFlightFence
  */

} // namespace MyonCore

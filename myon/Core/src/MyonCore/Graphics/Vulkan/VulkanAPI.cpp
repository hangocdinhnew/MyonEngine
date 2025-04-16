#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
VulkanAPI::VulkanAPI(SDL_Window *p_Window, const std::string &p_Title,
                     const std::string &p_Vert, const std::string &p_Frag)
    : m_Window(p_Window), m_Vert(p_Vert), m_Frag(p_Frag) {
  m_VulkanInstance = std::make_unique<VulkanInstance>(p_Title);
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
      m_Vert, m_Frag);
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
  m_VulkanBuffer = std::make_unique<VulkanBuffer>(
      m_VulkanDevice->getLogicalDevice(), m_VulkanDevice->getPhysicalDevice(),
      m_VulkanCommandBuffers->getCommandPool(),
      m_VulkanDevice->getGraphicsQueue());
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
      m_VulkanSyncObjects->getInFlightFence(),
      m_VulkanBuffer->getVertexBuffer());
  MYON_CORE_INFO("Initialized Vulkan!");
}

/*
  VulkanBuffer(vk::Device &p_LogicalDevice,
               vk::PhysicalDevice &p_PhysicalDevice, vk::CommandPool&
  p_CommandPool, vk::CommandBuffer& p_CommandBuffer, vk::Queue&
  p_GraphicsQueue);
*/

VulkanAPI::~VulkanAPI() { MYON_CORE_INFO("Shutting down Vulkan..."); }

void VulkanAPI::RecreateSwapchain() {
  int width, height;

  SDL_GetWindowSizeInPixels(m_Window, &width, &height);
  while (width == 0 || height == 0) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    SDL_GetWindowSizeInPixels(m_Window, &width, &height);
  }

  m_VulkanDevice->getLogicalDevice().waitIdle();

  m_VulkanSyncObjects.reset();

  m_VulkanCommandBuffers.reset();

  m_VulkanFramebuffer.reset();

  m_VulkanGraphicsPipeline.reset();

  m_VulkanRenderPass.reset();

  m_VulkanImageViews.reset();

  m_VulkanSwapchain.reset();

  m_VulkanSwapchain = std::make_unique<VulkanSwapChain>(
      m_Window, m_VulkanDevice->getPhysicalDevice(),
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
      m_Vert, m_Frag);
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

  m_VulkanRenderer->UpdateSwapchain(
      m_VulkanDevice->getGraphicsQueue(), m_VulkanDevice->getPresentQueue(),
      m_VulkanSwapchain->getSwapChain(),
      m_VulkanCommandBuffers->getCommandBuffer(),
      m_VulkanRenderPass->getRenderPass(),
      m_VulkanGraphicsPipeline->getGraphicsPipeline(),
      m_VulkanSwapchain->getSwapChainExtent(),
      m_VulkanFramebuffer->getSwapchainFramebuffers(),
      m_VulkanSyncObjects->getImageAvailableSemaphore(),
      m_VulkanSyncObjects->getRenderFinishedSemaphore(),
      m_VulkanSyncObjects->getInFlightFence());

  m_VulkanRenderer->ResetShouldRecreateSwapChain();
}

} // namespace MyonCore

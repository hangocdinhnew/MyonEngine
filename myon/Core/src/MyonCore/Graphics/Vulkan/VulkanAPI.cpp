#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
VulkanAPI::VulkanAPI(SDL_Window *p_Window, const std::string &p_Title,
                     const std::string &p_Vert, const std::string &p_Frag)
    : m_Window(p_Window), m_Vert(p_Vert), m_Frag(p_Frag) {
  // Instance
  m_VulkanInstanceConfig = VulkanInstanceConfig{.title = p_Title};
  m_VulkanInstance = std::make_unique<VulkanInstance>(m_VulkanInstanceConfig);

  // Validation Layer
  m_VulkanValidationLayerConfig = VulkanValidationLayerConfig{
      .p_Instance = m_VulkanInstance->getInstance()};
  m_VulkanValidationLayer =
      std::make_unique<VulkanValidationLayer>(m_VulkanValidationLayerConfig);

  // Surface
  m_VulkanSurfaceConfig = VulkanSurfaceConfig{
      .p_Window = m_Window, .p_Instance = m_VulkanInstance->getInstance()};
  m_VulkanSurface = std::make_unique<VulkanSurface>(m_VulkanSurfaceConfig);

  // Device
  m_VulkanDeviceConfig =
      VulkanDeviceConfig{.p_Instance = m_VulkanInstance->getInstance(),
                         .p_Surface = m_VulkanSurface->getSurface()};
  m_VulkanDevice = std::make_unique<VulkanDevice>(m_VulkanDeviceConfig);

  // SwapChain
  m_VulkanSwapChainConfig = VulkanSwapChainConfig{
      .p_Window = m_Window,
      .p_PhysicalDevice = m_VulkanDevice->getPhysicalDevice(),
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_Surface = m_VulkanSurface->getSurface()};
  m_VulkanSwapchain =
      std::make_unique<VulkanSwapChain>(m_VulkanSwapChainConfig);

  // Image Views
  m_VulkanImageViewsConfig = VulkanImageViewsConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_SwapChainImages = m_VulkanSwapchain->getSwapChainImages(),
      .p_SwapChainImageFormat = m_VulkanSwapchain->getSwapChainImageFormat()};
  m_VulkanImageViews =
      std::make_unique<VulkanImageViews>(m_VulkanImageViewsConfig);

  // Render Pass
  m_VulkanRenderPassConfig = VulkanRenderPassConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_SwapchainImageFormat = m_VulkanSwapchain->getSwapChainImageFormat(),
  };
  m_VulkanRenderPass =
      std::make_unique<VulkanRenderPass>(m_VulkanRenderPassConfig);

  // Graphics Pipeline
  m_VulkanGraphicsPipelineConfig = VulkanGraphicsPipelineConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_RenderPass = m_VulkanRenderPass->getRenderPass(),
      .vert = m_Vert,
      .frag = m_Frag};
  m_VulkanGraphicsPipeline =
      std::make_unique<VulkanGraphicsPipeline>(m_VulkanGraphicsPipelineConfig);

  // Framebuffer
  m_VulkanFramebufferConfig = VulkanFramebufferConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_RenderPass = m_VulkanRenderPass->getRenderPass(),
      .p_SwapChainImageViews = m_VulkanImageViews->getSwapChainImageViews(),
      .p_SwapChainExtent = m_VulkanSwapchain->getSwapChainExtent(),
  };
  m_VulkanFramebuffer =
      std::make_unique<VulkanFramebuffer>(m_VulkanFramebufferConfig);

  // Command buffers
  m_VulkanCommandBufferConfig = VulkanCommandBufferConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_PhysicalDevice = m_VulkanDevice->getPhysicalDevice(),
      .p_Surface = m_VulkanSurface->getSurface(),
      .p_RenderPass = m_VulkanRenderPass->getRenderPass(),
      .p_SwapChainFramebuffers =
          m_VulkanFramebuffer->getSwapchainFramebuffers(),
      .p_SwapChainExtent = m_VulkanSwapchain->getSwapChainExtent(),
      .p_GraphicsPipeline = m_VulkanGraphicsPipeline->getGraphicsPipeline(),
  };
  m_VulkanCommandBuffers =
      std::make_unique<VulkanCommandBuffer>(m_VulkanCommandBufferConfig);

  // Buffers (Vertex Buffers, Staging Buffers, Index Buffers, ...)
  m_VulkanBufferConfig = VulkanBufferConfig{
      .p_LogicalDevice = m_VulkanDevice->getLogicalDevice(),
      .p_PhysicalDevice = m_VulkanDevice->getPhysicalDevice(),
      .p_CommandPool = m_VulkanCommandBuffers->getCommandPool(),
      .p_GraphicsQueue = m_VulkanDevice->getGraphicsQueue()};
  m_VulkanBuffer = std::make_unique<VulkanBuffer>(m_VulkanBufferConfig);

  // Sync Objects
  m_VulkanSyncObjectsConfig = VulkanSyncObjectsConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
  };
  m_VulkanSyncObjects =
      std::make_unique<VulkanSyncObjects>(m_VulkanSyncObjectsConfig);

  // Renderer
  m_VulkanRendererConfig = VulkanRendererConfig{
      .p_Device = m_VulkanDevice->getLogicalDevice(),
      .p_GraphicsQueue = m_VulkanDevice->getGraphicsQueue(),
      .p_PresentQueue = m_VulkanDevice->getPresentQueue(),
      .p_SwapChain = m_VulkanSwapchain->getSwapChain(),
      .p_CommandBuffers = m_VulkanCommandBuffers->getCommandBuffer(),
      .p_RenderPass = m_VulkanRenderPass->getRenderPass(),
      .p_GraphicsPipeline = m_VulkanGraphicsPipeline->getGraphicsPipeline(),
      .p_SwapChainExtent = m_VulkanSwapchain->getSwapChainExtent(),
      .p_SwapChainFramebuffers =
          m_VulkanFramebuffer->getSwapchainFramebuffers(),
      .p_ImageAvailableSemaphores =
          m_VulkanSyncObjects->getImageAvailableSemaphore(),
      .p_RenderFinishedSemaphores =
          m_VulkanSyncObjects->getRenderFinishedSemaphore(),
      .p_InFlightFences = m_VulkanSyncObjects->getInFlightFence(),
      .p_VertexBuffer = m_VulkanBuffer->getVertexBuffer(),
      .p_IndexBuffer = m_VulkanBuffer->getIndexBuffer(),
  };
  m_VulkanRenderer = std::make_unique<VulkanRenderer>(m_VulkanRendererConfig);

  // Logs
  MYON_CORE_INFO("Initialized Vulkan!");
}

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

  // Swap chain
  m_VulkanSwapChainConfig.p_Window = m_Window;
  m_VulkanSwapChainConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanSwapChainConfig.p_PhysicalDevice =
      m_VulkanDevice->getPhysicalDevice();
  m_VulkanSwapChainConfig.p_Surface = m_VulkanSurface->getSurface();
  m_VulkanSwapchain =
      std::make_unique<VulkanSwapChain>(m_VulkanSwapChainConfig);

  // Image Views
  m_VulkanImageViewsConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanImageViewsConfig.p_SwapChainImages =
      m_VulkanSwapchain->getSwapChainImages();
  m_VulkanImageViewsConfig.p_SwapChainImageFormat =
      m_VulkanSwapchain->getSwapChainImageFormat();
  m_VulkanImageViews =
      std::make_unique<VulkanImageViews>(m_VulkanImageViewsConfig);

  // Render Pass
  m_VulkanRenderPassConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanRenderPassConfig.p_SwapchainImageFormat =
      m_VulkanSwapchain->getSwapChainImageFormat();
  m_VulkanRenderPass =
      std::make_unique<VulkanRenderPass>(m_VulkanRenderPassConfig);

  // Graphics Pipeline
  m_VulkanGraphicsPipelineConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanGraphicsPipelineConfig.p_RenderPass =
      m_VulkanRenderPass->getRenderPass();
  m_VulkanGraphicsPipeline =
      std::make_unique<VulkanGraphicsPipeline>(m_VulkanGraphicsPipelineConfig);

  // Framebuffer
  m_VulkanFramebufferConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanFramebufferConfig.p_RenderPass = m_VulkanRenderPass->getRenderPass();
  m_VulkanFramebufferConfig.p_SwapChainImageViews =
      m_VulkanImageViews->getSwapChainImageViews();
  m_VulkanFramebufferConfig.p_SwapChainExtent =
      m_VulkanSwapchain->getSwapChainExtent();
  m_VulkanFramebuffer =
      std::make_unique<VulkanFramebuffer>(m_VulkanFramebufferConfig);

  // Command Buffer
  m_VulkanCommandBufferConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanCommandBufferConfig.p_PhysicalDevice =
      m_VulkanDevice->getPhysicalDevice();
  m_VulkanCommandBufferConfig.p_Surface = m_VulkanSurface->getSurface();
  m_VulkanCommandBufferConfig.p_RenderPass =
      m_VulkanRenderPass->getRenderPass();
  m_VulkanCommandBufferConfig.p_SwapChainFramebuffers =
      m_VulkanFramebuffer->getSwapchainFramebuffers();
  m_VulkanCommandBufferConfig.p_SwapChainExtent =
      m_VulkanSwapchain->getSwapChainExtent();
  m_VulkanCommandBufferConfig.p_GraphicsPipeline =
      m_VulkanGraphicsPipeline->getGraphicsPipeline();
  m_VulkanCommandBuffers =
      std::make_unique<VulkanCommandBuffer>(m_VulkanCommandBufferConfig);

  // Sync Objects
  m_VulkanSyncObjectsConfig.p_Device = m_VulkanDevice->getLogicalDevice();
  m_VulkanSyncObjects =
      std::make_unique<VulkanSyncObjects>(m_VulkanSyncObjectsConfig);

  // Renderer
  m_VulkanRendererConfig.p_SwapChain = m_VulkanSwapchain->getSwapChain();
  m_VulkanRendererConfig.p_GraphicsQueue = m_VulkanDevice->getGraphicsQueue();
  m_VulkanRendererConfig.p_PresentQueue = m_VulkanDevice->getPresentQueue();
  m_VulkanRendererConfig.p_RenderPass = m_VulkanRenderPass->getRenderPass();
  m_VulkanRendererConfig.p_CommandBuffers = m_VulkanCommandBuffers->getCommandBuffer();

  m_VulkanRendererConfig.p_GraphicsPipeline = m_VulkanGraphicsPipeline->getGraphicsPipeline();

  m_VulkanRendererConfig.p_SwapChainExtent = m_VulkanSwapchain->getSwapChainExtent();
  m_VulkanRendererConfig.p_SwapChainFramebuffers = m_VulkanFramebuffer->getSwapchainFramebuffers();

  m_VulkanRendererConfig.p_ImageAvailableSemaphores = m_VulkanSyncObjects->getImageAvailableSemaphore();
  m_VulkanRendererConfig.p_RenderFinishedSemaphores = m_VulkanSyncObjects->getRenderFinishedSemaphore();
  m_VulkanRendererConfig.p_InFlightFences = m_VulkanSyncObjects->getInFlightFence();

  m_VulkanRenderer->UpdateSwapchain(m_VulkanRendererConfig);

  m_VulkanRenderer->ResetShouldRecreateSwapChain();
}

} // namespace MyonCore

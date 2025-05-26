// clang-format off
#pragma once
#include "MyonCore/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanValidationLayer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanDevice.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanSurface.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanSwapChain.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanImageViews.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanRenderPass.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanGraphicsPipeline.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanFramebuffer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanCommandBuffers.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanBuffer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanSyncObjects.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanRenderer.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace Vulkan {
class VulkanAPI {
public:
  VulkanAPI(SDL_Window *p_Window, const std::string &p_Title,
            const std::string &p_Vert, const std::string &pFrag);
  ~VulkanAPI();

  void DrawFrame() { m_VulkanRenderer->DrawFrame(); }

  vk::Device getLogicalDevice() { return m_VulkanDevice->getLogicalDevice(); }

  void RecreateSwapchain();

  bool ShouldRecreateSwapChain() {
    return m_VulkanRenderer->ShouldRecreateSwapChain();
  }

private:
  std::unique_ptr<VulkanInstance> m_VulkanInstance;
  std::unique_ptr<VulkanValidationLayer> m_VulkanValidationLayer;
  std::unique_ptr<VulkanSurface> m_VulkanSurface;
  std::unique_ptr<VulkanDevice> m_VulkanDevice;
  std::unique_ptr<VulkanSwapChain> m_VulkanSwapchain;
  std::unique_ptr<VulkanImageViews> m_VulkanImageViews;
  std::unique_ptr<VulkanRenderPass> m_VulkanRenderPass;
  std::unique_ptr<VulkanGraphicsPipeline> m_VulkanGraphicsPipeline;
  std::unique_ptr<VulkanFramebuffer> m_VulkanFramebuffer;
  std::unique_ptr<VulkanCommandBuffer> m_VulkanCommandBuffers;
  std::unique_ptr<VulkanBuffer> m_VulkanBuffer;
  std::unique_ptr<VulkanSyncObjects> m_VulkanSyncObjects;
  std::unique_ptr<VulkanRenderer> m_VulkanRenderer;

  SDL_Window *m_Window;

  const std::string &m_Vert;
  const std::string &m_Frag;

  VulkanInstanceConfig m_VulkanInstanceConfig;
  VulkanValidationLayerConfig m_VulkanValidationLayerConfig;
  VulkanSurfaceConfig m_VulkanSurfaceConfig;
  VulkanDeviceConfig m_VulkanDeviceConfig;
  VulkanSwapChainConfig m_VulkanSwapChainConfig;
  VulkanImageViewsConfig m_VulkanImageViewsConfig;
  VulkanRenderPassConfig m_VulkanRenderPassConfig;
  VulkanGraphicsPipelineConfig m_VulkanGraphicsPipelineConfig;
  VulkanFramebufferConfig m_VulkanFramebufferConfig;
  VulkanCommandBufferConfig m_VulkanCommandBufferConfig;
  VulkanBufferConfig m_VulkanBufferConfig;
  VulkanSyncObjectsConfig m_VulkanSyncObjectsConfig;
  VulkanRendererConfig m_VulkanRendererConfig;
};
} // namespace Vulkan
} // namespace Graphics
} // namespace MyonCore

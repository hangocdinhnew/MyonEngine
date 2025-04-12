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
#include "MyonCore/Graphics/Vulkan/VulkanSyncObjects.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanRenderer.hpp"
// clang-format on

namespace MyonCore {
class VulkanAPI {
public:
  VulkanAPI(SDL_Window *p_Window, const std::string &title,
            const std::string vert, const std::string frag);
  ~VulkanAPI();

  void DrawFrame() {
    m_VulkanRenderer->DrawFrame();
  }

  vk::Device getLogicalDevice() {
    return m_VulkanDevice->getLogicalDevice();
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
  std::unique_ptr<VulkanSyncObjects> m_VulkanSyncObjects;
  std::unique_ptr<VulkanRenderer> m_VulkanRenderer;
};
} // namespace MyonCore

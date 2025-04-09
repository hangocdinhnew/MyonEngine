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
// clang-format on

namespace MyonCore {
class VulkanAPI {
public:
  VulkanAPI(SDL_Window *p_Window, const std::string &title,
            const std::string vert, const std::string frag);
  ~VulkanAPI();

private:
  std::unique_ptr<VulkanInstance> m_VulkanInstance;
  std::unique_ptr<VulkanValidationLayer> m_VulkanValidationLayer;
  std::unique_ptr<VulkanSurface> m_VulkanSurface;
  std::unique_ptr<VulkanDevice> m_VulkanDevice;
  std::unique_ptr<VulkanSwapChain> m_VulkanSwapchain;
  std::unique_ptr<VulkanImageViews> m_VulkanImageViews;
  std::unique_ptr<VulkanRenderPass> m_VulkanRenderPass;
  std::unique_ptr<VulkanGraphicsPipeline> m_VulkanGraphicsPipeline;
};
} // namespace MyonCore

// clang-format off
#pragma once
#include "MyonCore/Graphics/Vulkan/VulkanInstance.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanValidationLayer.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanDevice.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanSurface.hpp"
#include "MyonCore/Graphics/Vulkan/VulkanSwapChain.hpp"
// clang-format on

namespace MyonCore {
class VulkanAPI {
public:
  VulkanAPI(SDL_Window* p_Window, const std::string &title);
  ~VulkanAPI();

private:
  std::unique_ptr<VulkanInstance> m_Instance;
  std::unique_ptr<VulkanValidationLayer> m_ValidationLayer;
  std::unique_ptr<VulkanSurface> m_VulkanSurface;
  std::unique_ptr<VulkanDevice> m_VulkanDevice;
  std::unique_ptr<VulkanSwapChain> m_Swapchain;
};
} // namespace MyonCore

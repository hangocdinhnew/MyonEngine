#pragma once
#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
namespace Graphics {
class GraphicsAPI {
public:
  GraphicsAPI(SDL_Window *p_Window, const std::string &title,
              const std::string &vert, const std::string &frag);
  ~GraphicsAPI() = default;

  void DrawFrame() { m_VulkanAPI->DrawFrame(); }

  vk::Device getLogicalDevice() { return m_VulkanAPI->getLogicalDevice(); }

  void RecreateSwapchain() { m_VulkanAPI->RecreateSwapchain(); }

  bool ShouldRecreateSwapChain() {
    return m_VulkanAPI->ShouldRecreateSwapChain();
  }

private:
  std::unique_ptr<Vulkan::VulkanAPI> m_VulkanAPI;
};
} // namespace Graphics
} // namespace MyonCore

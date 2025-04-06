#pragma once
#include "MyonCore/Graphics/Vulkan/VulkanAPI.hpp"

namespace MyonCore {
class GraphicsAPI {
public:
  GraphicsAPI(SDL_Window *p_Window, const std::string &title,
              const std::string vert, const std::string frag);
  ~GraphicsAPI() = default;

private:
  std::unique_ptr<VulkanAPI> m_VulkanAPI;
};
} // namespace MyonCore

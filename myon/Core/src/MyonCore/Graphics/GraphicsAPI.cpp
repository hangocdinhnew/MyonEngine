#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
GraphicsAPI::GraphicsAPI(SDL_Window* p_Window, const std::string &title) {
  m_VulkanAPI = std::make_unique<VulkanAPI>(p_Window, title);
}
}

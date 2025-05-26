#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI(SDL_Window *p_Window, const std::string &title,
                         const std::string &vert, const std::string &frag) {
  m_VulkanAPI =
      std::make_unique<Vulkan::VulkanAPI>(p_Window, title, vert, frag);
}
} // namespace Graphics
} // namespace MyonCore

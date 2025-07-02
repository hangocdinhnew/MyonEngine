#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI(SDL_Window *m_Window, std::string &title,
                         std::string &computeFolderName,
                         std::string &computeFileName) {
  m_WebGPUAPI = std::make_unique<WebGPU::WebGPUAPI>(m_Window, title, computeFolderName, computeFileName);
}
} // namespace Graphics
} // namespace MyonCore

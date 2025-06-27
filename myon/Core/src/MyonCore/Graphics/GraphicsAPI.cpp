#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI(SDL_Window *m_Window, std::string &title) {
  m_WebGPUAPI = std::make_unique<WebGPU::WebGPUAPI>(m_Window, title);
}

void GraphicsAPI::PollDevice() { m_WebGPUAPI->PollDevices(); }
} // namespace Graphics
} // namespace MyonCore

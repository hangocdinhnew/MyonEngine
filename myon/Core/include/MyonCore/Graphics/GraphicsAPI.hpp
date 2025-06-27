#pragma once

// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
class GraphicsAPI {
public:
  GraphicsAPI(SDL_Window *m_Window, std::string &title);
  ~GraphicsAPI() = default;

  void PollDevice();

private:
  std::unique_ptr<WebGPU::WebGPUAPI> m_WebGPUAPI;
};
} // namespace Graphics
} // namespace MyonCore

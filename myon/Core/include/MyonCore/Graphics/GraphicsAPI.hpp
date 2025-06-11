#pragma once

// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
class GraphicsAPI {
public:
  GraphicsAPI();
  ~GraphicsAPI() = default;

private:
  std::unique_ptr<WebGPU::WebGPUAPI> m_WebGPUAPI;
};
} // namespace Graphics
} // namespace MyonCore

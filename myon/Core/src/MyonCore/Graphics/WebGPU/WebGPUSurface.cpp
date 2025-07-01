// clang-format off
#include <sdl3webgpu.h>

#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUSurface.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUSurface::WebGPUSurface(WebGPUSurfaceConfig& p_SurfaceConfig) : m_Window(p_SurfaceConfig.p_Window), m_Instance(p_SurfaceConfig.p_Instance) {
  MYON_CORE_ASSERT(!m_Instance.has_value(), "Surface - Failed to access m_Instance!");
  MYON_CORE_ASSERT(!m_Window.has_value(), "Surface - Failed to access m_Window!");

  m_Surface = SDL_GetWGPUSurface(m_Instance.value(), m_Window.value());

  MYON_CORE_INFO("WebGPU - Surface created!");
}

WebGPUSurface::~WebGPUSurface() {
  MYON_CORE_INFO("WebGPU - Destroying surface...");

  m_Surface.release();
}
}
} // namespace Graphics
} // namespace MyonCore

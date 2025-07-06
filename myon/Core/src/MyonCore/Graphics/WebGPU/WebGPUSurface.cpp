// clang-format off
#include <sdl3webgpu.h>

#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUSurface.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUSurface::WebGPUSurface(WebGPUSurfaceConfig &p_SurfaceConfig)
    : m_Window(p_SurfaceConfig.p_Window),
      m_Instance(p_SurfaceConfig.p_Instance) {
  MYON_CORE_ASSERT(!m_Instance.has_value(),
                   "Surface - Failed to access m_Instance!");

  MYON_CORE_ASSERT(!m_Window.has_value(),
                   "Surface - Failed to access m_Window!");

  m_Surface = SDL_GetWGPUSurface(m_Instance.value(), m_Window.value());

  MYON_CORE_INFO("WebGPU - Surface created!");
}

WebGPUSurface::~WebGPUSurface() {
  MYON_CORE_INFO("WebGPU - Destroying surface...");

  wgpuSurfaceRelease(m_Surface);
}

void WebGPUSurface::configureSurface(WGPUAdapter &p_Adapter,
                                     WGPUDevice &p_Device) {
  m_SurfaceConfig = {};

  int width, height;
  SDL_GetWindowSize(m_Window.value(), &width, &height);

  m_SurfaceConfig.width = width;
  m_SurfaceConfig.height = height;
  m_SurfaceConfig.device = p_Device;

  m_SurfaceCapabilities = {};

  WGPUStatus status =
      wgpuSurfaceGetCapabilities(m_Surface, p_Adapter, &m_SurfaceCapabilities);
  MYON_CORE_ASSERT(status != WGPUStatus_Success,
                   "WebGPU - Failed to get capabilities of Surface!");

  m_SurfaceConfig.format = m_SurfaceCapabilities.formats[0];
  m_SurfaceConfig.usage = WGPUTextureUsage_RenderAttachment;

  m_SurfaceConfig.presentMode = WGPUPresentMode_Fifo;
  m_SurfaceConfig.alphaMode = WGPUCompositeAlphaMode_Auto;

  wgpuSurfaceConfigure(m_Surface, &m_SurfaceConfig);
}

void WebGPUSurface::unconfigureSurface() {
  wgpuSurfaceCapabilitiesFreeMembers(m_SurfaceCapabilities);
  wgpuSurfaceUnconfigure(m_Surface);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

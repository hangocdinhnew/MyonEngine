// clang-format off
#include <optional>

#include <webgpu/webgpu.h>
#include <SDL3/SDL.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUSurfaceConfig {
  std::optional<WGPUInstance> p_Instance;
  std::optional<SDL_Window *> p_Window;
};

class WebGPUSurface {
public:
  WebGPUSurface(WebGPUSurfaceConfig &p_SurfaceConfig);
  ~WebGPUSurface();

  WGPUSurface &getSurface() { return m_Surface; }
  WGPUSurfaceConfiguration &getSurfaceConfiguration() {
    return m_SurfaceConfig;
  }
  WGPUSurfaceCapabilities &getSurfaceCapabilities() {
    return m_SurfaceCapabilities;
  }

  void configureSurface(WGPUAdapter &p_Adapter, WGPUDevice &p_Device);
  void unconfigureSurface();

private:
  std::optional<WGPUInstance> &m_Instance;
  std::optional<SDL_Window *> &m_Window;

  WGPUSurface m_Surface;
  WGPUSurfaceConfiguration m_SurfaceConfig;
  WGPUSurfaceCapabilities m_SurfaceCapabilities;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

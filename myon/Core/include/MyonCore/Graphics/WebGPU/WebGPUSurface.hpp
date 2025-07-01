// clang-format off
#include <optional>

#include <webgpu/webgpu.hpp>
#include <SDL3/SDL.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUSurfaceConfig {
  std::optional<wgpu::Instance> p_Instance;
  std::optional<SDL_Window *> p_Window;
};

class WebGPUSurface {
public:
  WebGPUSurface(WebGPUSurfaceConfig &p_SurfaceConfig);
  ~WebGPUSurface();

  wgpu::Surface &getSurface() { return m_Surface; }

private:
  std::optional<wgpu::Instance> &m_Instance;
  std::optional<SDL_Window *> &m_Window;

  wgpu::Surface m_Surface;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

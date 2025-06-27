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

private:
  std::optional<WGPUInstance> &m_Instance;
  std::optional<SDL_Window *> &m_Window;

  WGPUSurface m_Surface;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

// clang-format off
#include <optional>
#include <webgpu/webgpu.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUAdapterConfig {
  std::optional<wgpu::Instance> p_Instance;
  std::optional<wgpu::Surface> p_Surface;
};

class WebGPUAdapter {
public:
  WebGPUAdapter(WebGPUAdapterConfig &p_AdapterConfig);
  ~WebGPUAdapter();

  wgpu::Adapter &getAdapter() { return m_Adapter; }

private:
  std::optional<wgpu::Instance> &m_Instance;
  std::optional<wgpu::Surface> &m_Surface;

  wgpu::Adapter m_Adapter;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

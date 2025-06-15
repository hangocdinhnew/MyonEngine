// clang-format off
#include <optional>
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUAdapterConfig {
  std::optional<WGPUInstance> p_Instance;
};

class WebGPUAdapter {
public:
  WebGPUAdapter(WebGPUAdapterConfig &p_AdapterConfig);
  ~WebGPUAdapter();

  WGPUAdapter getAdapter() { return m_Adapter; }

private:
  std::optional<WGPUInstance> &m_Instance;

  WGPUAdapter m_Adapter;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

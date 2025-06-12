// clang-format off
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUAdapterConfig {
  WGPUInstance p_Instance;
};

class WebGPUAdapter {
public:
  WebGPUAdapter(WebGPUAdapterConfig& p_AdapterConfig);
  ~WebGPUAdapter();

  WGPUAdapter getAdapter() { return m_Adapter; }

private:
  WGPUInstance &m_Instance;

  WGPUAdapter m_Adapter;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

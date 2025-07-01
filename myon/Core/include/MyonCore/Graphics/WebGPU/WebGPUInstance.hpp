#pragma once

// clang-format off
#include "webgpu/webgpu.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
class WebGPUInstance {
public:
  WebGPUInstance();
  ~WebGPUInstance();

  wgpu::Instance &getInstance() { return m_Instance; }

private:
  wgpu::Instance m_Instance;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

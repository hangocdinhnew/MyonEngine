#pragma once

// clang-format off
#include "webgpu/webgpu.h"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
class WebGPUInstance {
public:
  WebGPUInstance();
  ~WebGPUInstance();

  WGPUInstance &getInstance() { return m_Instance; }

private:
  WGPUInstance m_Instance;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

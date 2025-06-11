#pragma once

// clang-format off
#include <memory>

#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
class WebGPUAPI {
public:
  WebGPUAPI();
  ~WebGPUAPI();

private:
  std::unique_ptr<WebGPUInstance> m_WebGPUInstance;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include <memory>

#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
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
  std::unique_ptr<WebGPUAdapter> m_WebGPUAdapter;

  WebGPUAdapterConfig m_WebGPUAdapterConfig;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include <memory>

#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUDevice.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
class WebGPUAPI {
public:
  WebGPUAPI(std::string &name);
  ~WebGPUAPI();

private:
  std::unique_ptr<WebGPUInstance> m_WebGPUInstance;
  std::unique_ptr<WebGPUAdapter> m_WebGPUAdapter;
  std::unique_ptr<WebGPUDevice> m_WebGPUDevice;

  WebGPUAdapterConfig m_WebGPUAdapterConfig;
  WebGPUDeviceConfig m_WebGPUDeviceConfig;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

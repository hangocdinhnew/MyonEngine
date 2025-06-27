#pragma once

// clang-format off
#include <memory>

#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUDevice.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUCommandQueue.hpp"
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
  std::unique_ptr<WebGPUCommandQueue> m_WebGPUCommandQueue;

  WebGPUAdapterConfig m_WebGPUAdapterConfig;
  WebGPUDeviceConfig m_WebGPUDeviceConfig;
  WebGPUCommandQueueConfig m_WebGPUCommandQueueConfig;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

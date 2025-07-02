#pragma once

// clang-format off
#include <webgpu/wgpu.h>
#include <memory>

#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUSurface.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAdapter.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUDevice.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUBuffer.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUCommandQueue.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUComputePipeline.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
class WebGPUAPI {
public:
  WebGPUAPI(SDL_Window *m_Window, std::string &title,
            std::string &computeFolderName, std::string &computeFileName);
  ~WebGPUAPI();

  void PollDevices() {
    wgpuInstanceProcessEvents(m_WebGPUInstance->getInstance());
  }

  void FetchComputeBufferDataSync();

private:
  std::unique_ptr<WebGPUInstance> m_WebGPUInstance;
  std::unique_ptr<WebGPUSurface> m_WebGPUSurface;
  std::unique_ptr<WebGPUAdapter> m_WebGPUAdapter;
  std::unique_ptr<WebGPUDevice> m_WebGPUDevice;
  std::unique_ptr<WebGPUBuffer> m_WebGPUBuffer;
  std::unique_ptr<WebGPUCommandQueue> m_WebGPUCommandQueue;
  std::unique_ptr<WebGPUComputePipeline> m_WebGPUComputePipeline;

  WebGPUSurfaceConfig m_WebGPUSurfaceConfig;
  WebGPUAdapterConfig m_WebGPUAdapterConfig;
  WebGPUDeviceConfig m_WebGPUDeviceConfig;
  WebGPUBufferConfig m_WebGPUBufferConfig;
  WebGPUCommandQueueConfig m_WebGPUCommandQueueConfig;
  WebGPUComputePipelineConfig m_WebGPUComputePipelineConfig;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

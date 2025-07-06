#pragma once

// clang-format off
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonRHI {
enum class GPUBackend {
  None = 0,
  WebGPU = 0,
};

struct WebGPUSurfaceHandle {
  WGPUSurface surface;
  WGPUSurfaceConfiguration surfaceConfig;
  WGPUSurfaceCapabilities surfaceCapabilities;
};

struct GPUSurface {
  GPUBackend backend = GPUBackend::WebGPU;

  union {
    WebGPUSurfaceHandle webgpu;
  };
};

struct WebGPUQueueHandle {
  WGPUQueue queue;
  WGPUQueueDescriptor queueDesc;
};

struct GPUQueue {
  GPUBackend backend = GPUBackend::WebGPU;

  union {
    WebGPUQueueHandle webgpu;
  };
};

struct WebGPUDeviceHandle {
  WGPUDevice device;
  WGPUDeviceDescriptor deviceDesc;
};

struct GPUDevice {
  GPUBackend backend = GPUBackend::WebGPU;

  union {
    WebGPUDeviceHandle webgpu;
  };
};
} // namespace MyonRHI

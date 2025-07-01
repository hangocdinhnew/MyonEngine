#pragma once

// clang-format off
#include <optional>

#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUBufferConfig {
  std::optional<WGPUDevice> p_Device;
};

class WebGPUBuffer {
public:
  WebGPUBuffer(WebGPUBufferConfig &p_BufferConfig);
  ~WebGPUBuffer();

  WGPUBuffer getBufferA() { return m_BufferA; };
  WGPUBuffer getBufferB() { return m_BufferB; };
  WGPUBufferDescriptor getBufferADesc() { return m_BufferADesc; };
  WGPUBufferDescriptor getBufferBDesc() { return m_BufferBDesc; };

private:
  std::optional<WGPUDevice> &m_Device;

  WGPUBuffer m_BufferA;
  WGPUBuffer m_BufferB;
  WGPUBufferDescriptor m_BufferADesc;
  WGPUBufferDescriptor m_BufferBDesc;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

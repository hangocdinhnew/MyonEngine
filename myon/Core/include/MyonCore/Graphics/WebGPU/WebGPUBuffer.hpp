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

  WGPUBuffer getInputBuffer() { return m_InputBuffer; };
  WGPUBuffer getOutputBuffer() { return m_OutputBuffer; };
  WGPUBuffer getStagingBuffer() { return m_StagingBuffer; };
  WGPUBufferDescriptor getInputBufferDesc() { return m_InputBufferDesc; };
  WGPUBufferDescriptor getOutputBufferDesc() { return m_OutputBufferDesc; };
  WGPUBufferDescriptor getStagingBufferDesc() { return m_StagingBufferDesc; };

private:
  std::optional<WGPUDevice> &m_Device;

  WGPUBuffer m_InputBuffer;
  WGPUBuffer m_OutputBuffer;
  WGPUBuffer m_StagingBuffer;
  WGPUBufferDescriptor m_InputBufferDesc;
  WGPUBufferDescriptor m_OutputBufferDesc;
  WGPUBufferDescriptor m_StagingBufferDesc;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

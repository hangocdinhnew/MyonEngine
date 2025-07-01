#pragma once

// clang-format off
#include <optional>

#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUCommandQueueConfig {
  std::optional<WGPUInstance> p_Instance;
  std::optional<WGPUDevice> p_Device;
  std::optional<WGPUBuffer> p_BufferA;
  std::optional<WGPUBuffer> p_BufferB;
  std::optional<WGPUBufferDescriptor> p_BufferADesc;
  std::optional<WGPUBufferDescriptor> p_BufferBDesc;
};

class WebGPUCommandQueue {
public:
  WebGPUCommandQueue(WebGPUCommandQueueConfig &p_CommandQueueConfig);
  ~WebGPUCommandQueue();

  WGPUQueue &getQueue() { return m_Queue; }
  WGPUCommandEncoder &getEncoder() { return m_Encoder; }
  WGPUCommandBuffer &getCommand() { return m_Command; }

private:
  std::optional<WGPUInstance> &m_Instance;
  std::optional<WGPUDevice> &m_Device;
  std::optional<WGPUBuffer>& m_BufferA;
  std::optional<WGPUBuffer>& m_BufferB;
  std::optional<WGPUBufferDescriptor>& m_BufferADesc;
  std::optional<WGPUBufferDescriptor>& m_BufferBDesc;

  WGPUQueue m_Queue;
  WGPUCommandEncoder m_Encoder;
  WGPUCommandBuffer m_Command;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

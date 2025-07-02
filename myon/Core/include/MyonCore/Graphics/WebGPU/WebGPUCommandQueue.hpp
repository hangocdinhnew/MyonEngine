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
  std::optional<WGPUBuffer> p_OutputBuffer;
  std::optional<WGPUBuffer> p_StagingBuffer;
  std::optional<WGPUBufferDescriptor> p_OutputBufferDesc;
  std::optional<WGPUBufferDescriptor> p_StagingBufferDesc;
  std::optional<WGPUComputePipeline> p_ComputePipeline;
  std::optional<WGPUBindGroup> p_BindGroup;
};

class WebGPUCommandQueue {
public:
  WebGPUCommandQueue(WebGPUCommandQueueConfig &p_CommandQueueConfig);
  ~WebGPUCommandQueue();

  WGPUQueue &getQueue() { return m_Queue; }
  WGPUCommandEncoder &getEncoder() { return m_Encoder; }
  WGPUComputePassEncoder &getComputePass() { return m_ComputePass; }
  WGPUCommandBuffer &getCommand() { return m_Command; }

private:
  std::optional<WGPUInstance> &m_Instance;
  std::optional<WGPUDevice> &m_Device;
  std::optional<WGPUBuffer> &m_OutputBuffer;
  std::optional<WGPUBuffer> &m_StagingBuffer;
  std::optional<WGPUBufferDescriptor> &m_OutputBufferDesc;
  std::optional<WGPUBufferDescriptor> &m_StagingBufferDesc;
  std::optional<WGPUComputePipeline> &m_ComputePipeline;
  std::optional<WGPUBindGroup> &m_BindGroup;

  WGPUQueue m_Queue;
  WGPUCommandEncoder m_Encoder;
  WGPUComputePassEncoder m_ComputePass;
  WGPUCommandBuffer m_Command;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

#pragma once

// clang-format off
#include <optional>

#include <webgpu/webgpu.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUCommandQueueConfig {
  std::optional<wgpu::Instance> p_Instance;
  std::optional<wgpu::Device> p_Device;
  std::optional<wgpu::Buffer> p_BufferA;
  std::optional<wgpu::Buffer> p_BufferB;
  std::optional<wgpu::BufferDescriptor> p_BufferADesc;
  std::optional<wgpu::BufferDescriptor> p_BufferBDesc;
};

class WebGPUCommandQueue {
public:
  WebGPUCommandQueue(WebGPUCommandQueueConfig &p_CommandQueueConfig);
  ~WebGPUCommandQueue();

  wgpu::Queue &getQueue() { return m_Queue; }
  wgpu::CommandEncoder &getEncoder() { return m_Encoder; }
  wgpu::CommandBuffer &getCommand() { return m_Command; }

private:
  std::optional<wgpu::Instance> &m_Instance;
  std::optional<wgpu::Device> &m_Device;
  std::optional<wgpu::Buffer>& m_BufferA;
  std::optional<wgpu::Buffer>& m_BufferB;
  std::optional<wgpu::BufferDescriptor>& m_BufferADesc;
  std::optional<wgpu::BufferDescriptor>& m_BufferBDesc;

  wgpu::Queue m_Queue;
  wgpu::CommandEncoder m_Encoder;
  wgpu::CommandBuffer m_Command;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

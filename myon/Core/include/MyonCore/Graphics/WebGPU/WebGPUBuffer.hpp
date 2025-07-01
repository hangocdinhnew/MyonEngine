#pragma once

// clang-format off
#include <optional>

#include <webgpu/webgpu.hpp>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
struct WebGPUBufferConfig {
  std::optional<wgpu::Device> p_Device;
};

class WebGPUBuffer {
public:
  WebGPUBuffer(WebGPUBufferConfig &p_BufferConfig);
  ~WebGPUBuffer();

  wgpu::Buffer getBufferA() { return m_BufferA; };
  wgpu::Buffer getBufferB() { return m_BufferB; };
  wgpu::BufferDescriptor getBufferADesc() { return m_BufferADesc; };
  wgpu::BufferDescriptor getBufferBDesc() { return m_BufferBDesc; };

private:
  std::optional<wgpu::Device> &m_Device;

  wgpu::Buffer m_BufferA;
  wgpu::Buffer m_BufferB;
  wgpu::BufferDescriptor m_BufferADesc;
  wgpu::BufferDescriptor m_BufferBDesc;
};
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

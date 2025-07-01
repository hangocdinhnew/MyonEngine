// clang-format off
#include "MyonCore/Core/Log.hpp"

#include "MyonCore/Graphics/WebGPU/WebGPUBuffer.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUBuffer::WebGPUBuffer(WebGPUBufferConfig &p_BufferConfig)
    : m_Device(p_BufferConfig.p_Device) {
  MYON_CORE_ASSERT(!m_Device.has_value(),
                   "Buffer - Failed to access m_Device!");

  m_BufferADesc = wgpu::Default;
  m_BufferADesc.size = 256;
  m_BufferADesc.usage = wgpu::BufferUsage::MapWrite | wgpu::BufferUsage::CopySrc;
  m_BufferADesc.label = toWGPUStringView("Buffer A");
  m_BufferADesc.mappedAtCreation = true;
  m_BufferA = m_Device.value().createBuffer(m_BufferADesc);

  m_BufferBDesc = wgpu::Default;
  m_BufferBDesc.size = 32;
  m_BufferBDesc.usage = wgpu::BufferUsage::MapRead | wgpu::BufferUsage::CopyDst;
  m_BufferBDesc.label = toWGPUStringView("Buffer B");
  m_BufferB = m_Device.value().createBuffer(m_BufferBDesc);

  uint8_t *bufferDataA = static_cast<uint8_t *>(
      m_BufferA.getMappedRange(0, WGPU_WHOLE_MAP_SIZE));

  for (size_t i = 0; i < 256; ++i) {
    bufferDataA[i] = i;
  }

  m_BufferA.unmap();

  MYON_CORE_INFO("WebGPU - Buffer created!");
}

WebGPUBuffer::~WebGPUBuffer() {
  MYON_CORE_INFO("WebGPU - Buffer destroying...");

  m_BufferB.release();
  m_BufferA.release();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

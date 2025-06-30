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

  m_BufferADesc = {};
  m_BufferADesc.size = 256;
  m_BufferADesc.usage = WGPUBufferUsage_MapWrite | WGPUBufferUsage_CopySrc;
  m_BufferADesc.label = toWGPUStringView("Buffer A");
  m_BufferADesc.mappedAtCreation = true;
  m_BufferA = wgpuDeviceCreateBuffer(m_Device.value(), &m_BufferADesc);

  m_BufferBDesc = {};
  m_BufferBDesc.size = 32;
  m_BufferBDesc.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
  m_BufferBDesc.label = toWGPUStringView("Buffer B");
  m_BufferB = wgpuDeviceCreateBuffer(m_Device.value(), &m_BufferBDesc);

  uint8_t *bufferDataA = static_cast<uint8_t *>(
      wgpuBufferGetMappedRange(m_BufferA, 0, WGPU_WHOLE_MAP_SIZE));

  for (size_t i = 0; i < 256; ++i) {
    bufferDataA[i] = static_cast<uint8_t>(i);
  }

  wgpuBufferUnmap(m_BufferA);

  MYON_CORE_INFO("WebGPU - Buffer created!");
}

WebGPUBuffer::~WebGPUBuffer() {
  MYON_CORE_INFO("WebGPU - Buffer destroying...");

  wgpuBufferRelease(m_BufferB);
  wgpuBufferRelease(m_BufferA);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

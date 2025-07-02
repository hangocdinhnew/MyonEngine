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

  m_InputBufferDesc = {};
  m_InputBufferDesc.size = ELEMENT_COUNT * sizeof(float);
  m_InputBufferDesc.usage = WGPUBufferUsage_Storage;
  m_InputBufferDesc.label = toWGPUStringView("Input Buffer");
  m_InputBufferDesc.mappedAtCreation = true;
  m_InputBuffer = wgpuDeviceCreateBuffer(m_Device.value(), &m_InputBufferDesc);

  m_OutputBufferDesc = {};
  m_OutputBufferDesc.size = ELEMENT_COUNT * sizeof(float);
  m_OutputBufferDesc.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopySrc;
  m_OutputBufferDesc.label = toWGPUStringView("Output Buffer");
  m_OutputBuffer =
      wgpuDeviceCreateBuffer(m_Device.value(), &m_OutputBufferDesc);

  m_StagingBufferDesc = {};
  m_StagingBufferDesc.label = toWGPUStringView("Staging Buffer");
  m_StagingBufferDesc.size = ELEMENT_COUNT * sizeof(float);
  m_StagingBufferDesc.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
  m_StagingBuffer =
      wgpuDeviceCreateBuffer(m_Device.value(), &m_StagingBufferDesc);

	float* inputBufferData = static_cast<float*>(
		wgpuBufferGetMappedRange(m_InputBuffer, 0, WGPU_WHOLE_MAP_SIZE)
	);

	for (size_t i = 0 ; i < ELEMENT_COUNT * sizeof(float); ++i) {
		inputBufferData[i] = static_cast<float>(i) * 0.1f;
	}

  wgpuBufferUnmap(m_InputBuffer);

  MYON_CORE_INFO("WebGPU - Buffer created!");
}

WebGPUBuffer::~WebGPUBuffer() {
  MYON_CORE_INFO("WebGPU - Buffer destroying...");

  wgpuBufferRelease(m_StagingBuffer);
  wgpuBufferRelease(m_OutputBuffer);
  wgpuBufferRelease(m_InputBuffer);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

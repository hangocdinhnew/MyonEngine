// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include <wgpu.h>
#include <webgpu.h>

#include "MyonCore/Graphics/WebGPU/WebGPUCommandQueue.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static uint32_t divideAndCeil(uint32_t p, uint32_t q) {
  return (p + q - 1) / q;
}

WebGPUCommandQueue::WebGPUCommandQueue(
    WebGPUCommandQueueConfig &p_CommandQueueConfig)
    : m_Instance(p_CommandQueueConfig.p_Instance),
      m_Device(p_CommandQueueConfig.p_Device),
      m_OutputBuffer(p_CommandQueueConfig.p_OutputBuffer),
      m_StagingBuffer(p_CommandQueueConfig.p_StagingBuffer),
      m_OutputBufferDesc(p_CommandQueueConfig.p_OutputBufferDesc),
      m_StagingBufferDesc(p_CommandQueueConfig.p_StagingBufferDesc),
      m_ComputePipeline(p_CommandQueueConfig.p_ComputePipeline),
      m_BindGroup(p_CommandQueueConfig.p_BindGroup) {
  MYON_CORE_ASSERT(!m_Instance.has_value(),
                   "Command Queue - Failed to access m_Instance!");
  MYON_CORE_ASSERT(!m_Device.has_value(),
                   "Command Queue - Failed to access m_Device!");
  MYON_CORE_ASSERT(!m_OutputBuffer.has_value(),
                   "Command Queue - Failed to access m_OutputBuffer!");
  MYON_CORE_ASSERT(!m_StagingBuffer.has_value(),
                   "Command Queue - Failed to access m_StagingBuffer!");
  MYON_CORE_ASSERT(!m_OutputBufferDesc.has_value(),
                   "Command Queue - Failed to access m_OutputBufferDesc!");
  MYON_CORE_ASSERT(!m_StagingBufferDesc.has_value(),
                   "Command Queue - Failed to access m_StagingBufferDesc!");
  MYON_CORE_ASSERT(!m_ComputePipeline.has_value(),
                   "Command Queue - Failed to access m_ComputePipeline!");
  MYON_CORE_ASSERT(!m_BindGroup.has_value(),
                   "Command Queue - Failed to access m_BindGroup!");

  auto onQueueWorkDone = [](WGPUQueueWorkDoneStatus status, void *, void *) {
    switch (status) {
    case WGPUQueueWorkDoneStatus_Success:
      MYON_CORE_INFO("WebGPU - Queue work done success!");
      break;
    case WGPUQueueWorkDoneStatus_InstanceDropped:
      MYON_CORE_ERROR("WebGPU - Queue work done with error: Instance Dropped!");
      break;
    case WGPUQueueWorkDoneStatus_Error:
      MYON_CORE_ERROR("WebGPU - Queue work done with error.");
      break;
    default:
      MYON_CORE_ERROR("WebGPU - Queue work done with unknown error: {}",
                      &""[static_cast<int>(status)]);
      break;
    }
  };

  m_Queue = wgpuDeviceGetQueue(m_Device.value());

  WGPUCommandEncoderDescriptor encoderDesc = {};
  encoderDesc.nextInChain = nullptr;
  encoderDesc.label = toWGPUStringView("WebGPU Command Encoder.");
  m_Encoder = wgpuDeviceCreateCommandEncoder(m_Device.value(), &encoderDesc);

	m_ComputePass = wgpuCommandEncoderBeginComputePass(m_Encoder, nullptr);
	wgpuComputePassEncoderSetPipeline(m_ComputePass, m_ComputePipeline.value());
	wgpuComputePassEncoderSetBindGroup(m_ComputePass, 0, m_BindGroup.value(), 0, nullptr);
	uint32_t workgroupSizeX = 32;
	uint32_t workgroupCountX = divideAndCeil(ELEMENT_COUNT * sizeof(float), workgroupSizeX);
	wgpuComputePassEncoderDispatchWorkgroups(m_ComputePass, workgroupCountX, 1, 1);
	wgpuComputePassEncoderEnd(m_ComputePass);
	wgpuComputePassEncoderRelease(m_ComputePass);

  wgpuCommandEncoderCopyBufferToBuffer(m_Encoder, m_OutputBuffer.value(), 0,
                                       m_StagingBuffer.value(), 0,
                                       m_StagingBufferDesc.value().size);

#ifdef MYON_DEBUG
  WGPUStringView marker1conv = toWGPUStringView("Marker1");
  WGPUStringView marker2conv = toWGPUStringView("Marker2");

  wgpuCommandEncoderInsertDebugMarker(m_Encoder, marker1conv);
  wgpuCommandEncoderInsertDebugMarker(m_Encoder, marker2conv);
#endif

  WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
  cmdBufferDescriptor.nextInChain = nullptr;
  cmdBufferDescriptor.label = toWGPUStringView("WebGPU Command Buffer.");

  m_Command = wgpuCommandEncoderFinish(m_Encoder, &cmdBufferDescriptor);

  wgpuQueueSubmit(m_Queue, 1, &m_Command);

  auto onQueuedWorkDone = [](WGPUQueueWorkDoneStatus status, void *userdata1,
                             void *userdata2) {
    if (status != WGPUQueueWorkDoneStatus_Success) {
      MYON_DO_CORE_ASSERT(
          "WebGPU - Queue Work Done with Status Error! This is suspicious.");
    }

    bool &workDone = *reinterpret_cast<bool *>(userdata1);
    workDone = true;
  };

  bool workDone = false;

  WGPUQueueWorkDoneCallbackInfo callbackInfo = {};
  callbackInfo.mode = WGPUCallbackMode_AllowProcessEvents;
  callbackInfo.callback = onQueuedWorkDone;
  callbackInfo.userdata1 = &workDone;

  wgpuQueueOnSubmittedWorkDone(m_Queue, callbackInfo);
  wgpuInstanceProcessEvents(m_Instance.value());

  while (!workDone) {
    sleepForMSec(200);

    wgpuInstanceProcessEvents(m_Instance.value());
  }

  MYON_CORE_INFO("WebGPU - Command queue created!");
}

WebGPUCommandQueue::~WebGPUCommandQueue() {
  MYON_CORE_INFO("WebGPU - Destroying Command Queue...");

  wgpuCommandBufferRelease(m_Command);
  wgpuCommandEncoderRelease(m_Encoder);
  wgpuQueueRelease(m_Queue);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

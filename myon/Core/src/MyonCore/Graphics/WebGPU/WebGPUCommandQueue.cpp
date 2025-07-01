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
WebGPUCommandQueue::WebGPUCommandQueue(
    WebGPUCommandQueueConfig &p_CommandQueueConfig)
    : m_Instance(p_CommandQueueConfig.p_Instance),
      m_Device(p_CommandQueueConfig.p_Device),
      m_BufferA(p_CommandQueueConfig.p_BufferA),
      m_BufferB(p_CommandQueueConfig.p_BufferB),
      m_BufferADesc(p_CommandQueueConfig.p_BufferADesc),
      m_BufferBDesc(p_CommandQueueConfig.p_BufferBDesc) {
  MYON_CORE_ASSERT(!m_Instance.has_value(),
                   "Command Queue - Failed to access m_Instance!");
  MYON_CORE_ASSERT(!m_Device.has_value(),
                   "Command Queue - Failed to access m_Device!");
  MYON_CORE_ASSERT(!m_BufferA.has_value(),
                   "Command Queue - Failed to access m_BufferA!");
  MYON_CORE_ASSERT(!m_BufferB.has_value(),
                   "Command Queue - Failed to access m_BufferB!");
  MYON_CORE_ASSERT(!m_BufferADesc.has_value(),
                   "Command Queue - Failed to access m_BufferADesc!");
  MYON_CORE_ASSERT(!m_BufferBDesc.has_value(),
                   "Command Queue - Failed to access m_BufferBDesc!");

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
  wgpuCommandEncoderCopyBufferToBuffer(m_Encoder, m_BufferA.value(), 16,
                                       m_BufferB.value(), 0,
                                       m_BufferBDesc.value().size);

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

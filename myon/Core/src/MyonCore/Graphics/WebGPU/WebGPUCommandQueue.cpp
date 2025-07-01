// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include <wgpu.h>

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

  m_Queue = m_Device.value().getQueue();

  wgpu::CommandEncoderDescriptor encoderDesc = {};
  encoderDesc.nextInChain = nullptr;
  encoderDesc.label = toWGPUStringView("WebGPU Command Encoder.");
  m_Encoder = m_Device.value().createCommandEncoder(encoderDesc);
  m_Encoder.copyBufferToBuffer(m_BufferA.value(), 16, m_BufferB.value(), 0,
                               m_BufferBDesc.value().size);

#ifdef MYON_DEBUG
  wgpu::StringView marker1conv = toWGPUStringView("Marker1");
  wgpu::StringView marker2conv = toWGPUStringView("Marker2");

  m_Encoder.insertDebugMarker(marker1conv);
  m_Encoder.insertDebugMarker(marker2conv);
#endif

  wgpu::CommandBufferDescriptor cmdBufferDescriptor = {};
  cmdBufferDescriptor.nextInChain = nullptr;
  cmdBufferDescriptor.label = toWGPUStringView("WebGPU Command Buffer.");

  m_Command = m_Encoder.finish(cmdBufferDescriptor);

  m_Queue.submit(1, &m_Command);

  auto onQueuedWorkDone = [](WGPUQueueWorkDoneStatus status, void *userdata1,
                             void *userdata2) {
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

    bool &workDone = *reinterpret_cast<bool *>(userdata1);
    workDone = true;
  };

  bool workDone = false;

  wgpu::QueueWorkDoneCallbackInfo callbackInfo = {};
  callbackInfo.mode = wgpu::CallbackMode::AllowProcessEvents;
  callbackInfo.callback = onQueuedWorkDone;
  callbackInfo.userdata1 = &workDone;

  m_Queue.onSubmittedWorkDone(callbackInfo);
  m_Instance.value().processEvents();

  while (!workDone) {
    sleepForMSec(200);

    m_Instance.value().processEvents();
  }

  MYON_CORE_INFO("WebGPU - Command queue created!");
}

WebGPUCommandQueue::~WebGPUCommandQueue() {
  MYON_CORE_INFO("WebGPU - Destroying Command Queue...");

  m_Command.release();
  m_Encoder.release();
  m_Queue.release();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

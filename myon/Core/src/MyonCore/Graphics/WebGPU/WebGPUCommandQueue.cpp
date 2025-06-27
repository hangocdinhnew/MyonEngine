// clang-format off
#include "MyonCore/Core/Log.hpp"
#include <wgpu.h>
#include <webgpu.h>

#include "MyonCore/Graphics/WebGPU/WebGPUCommandQueue.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUCommandQueue::WebGPUCommandQueue(
    WebGPUCommandQueueConfig &p_CommandQueueConfig)
    : m_Device(p_CommandQueueConfig.p_Device) {
  MYON_CORE_ASSERT(!m_Device.has_value(), "Command Queue - Failed to access m_Device!");

  m_Queue = wgpuDeviceGetQueue(m_Device.value());

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

  WGPUQueueWorkDoneCallbackInfo workDoneCallBack{};
  workDoneCallBack.nextInChain = nullptr;
  workDoneCallBack.callback = onQueueWorkDone;
  wgpuQueueOnSubmittedWorkDone(m_Queue, workDoneCallBack);

  WGPUCommandEncoderDescriptor encoderDesc = {};
  encoderDesc.nextInChain = nullptr;
  std::string_view label = "WebGPU Command Encoder";
  WGPUStringView labelconverted = {label.data(), label.size()};
  encoderDesc.label = labelconverted;

  m_Encoder = wgpuDeviceCreateCommandEncoder(m_Device.value(), &encoderDesc);

#ifdef MYON_DEBUG
  std::string_view marker1 = "Marker1";
  std::string_view marker2 = "Marker2";

  WGPUStringView marker1conv = {marker1.data(), marker1.size()};
  WGPUStringView marker2conv = {marker2.data(), marker2.size()};

  wgpuCommandEncoderInsertDebugMarker(m_Encoder, marker1conv);
  wgpuCommandEncoderInsertDebugMarker(m_Encoder, marker2conv);
#endif

  WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
  cmdBufferDescriptor.nextInChain = nullptr;
  std::string_view label2 = "WebGPU Command Buffer";
  WGPUStringView label2converted = {label2.data(), label2.size()};
  cmdBufferDescriptor.label = label2converted;

  m_Command = wgpuCommandEncoderFinish(m_Encoder, &cmdBufferDescriptor);

  wgpuQueueSubmit(m_Queue, 1, &m_Command);

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

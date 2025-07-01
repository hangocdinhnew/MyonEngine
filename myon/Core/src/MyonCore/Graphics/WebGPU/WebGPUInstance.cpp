// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"

#include <webgpu/wgpu.h>
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
static void WebGPULogCallback(WGPULogLevel m_Level, WGPUStringView m_Message,
                              void *m_Userdata) {
  std::string_view msgView = toStdStringView(m_Message);

  switch (m_Level) {
  case WGPULogLevel_Error:
    MYON_CORE_ERROR("WebGPU - {}", msgView);
    break;
  case WGPULogLevel_Warn:
    MYON_CORE_WARN("WebGPU - {}", msgView);
    break;
  case WGPULogLevel_Info:
    MYON_CORE_INFO("WebGPU - {}", msgView);
    break;
  case WGPULogLevel_Debug:
    MYON_CORE_DEBUG("WebGPU - {}", msgView);
    break;
  case WGPULogLevel_Trace:
    MYON_CORE_TRACE("WebGPU - {}", msgView);
    break;
  default:
    MYON_CORE_WARN("WebGPU (UnknownLevel: {}) {}", static_cast<int>(m_Level),
                   msgView);
    break;
  }
}

WebGPUInstance::WebGPUInstance() {
#if MYON_DEBUG
  wgpuSetLogLevel(WGPULogLevel_Trace);
#else
  wgpuSetLogLevel(WGPULogLevel_Info);
#endif

  wgpuSetLogCallback(WebGPULogCallback, nullptr);

  wgpu::InstanceDescriptor l_Desc = {};
  l_Desc.nextInChain = nullptr;

  m_Instance = wgpu::createInstance(l_Desc);
  MYON_CORE_ASSERT(!m_Instance, "WebGPU - Could not initialize WebGPU Instance!");

  MYON_CORE_INFO("WebGPU - WebGPU Instance initialized!");
}

WebGPUInstance::~WebGPUInstance() {
  MYON_CORE_INFO("WebGPU - Releasing WebGPU Instance...");

  m_Instance.release();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

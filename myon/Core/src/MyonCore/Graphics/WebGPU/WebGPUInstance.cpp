// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUInstance.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUInstance::WebGPUInstance() {
  WGPUInstanceDescriptor l_Desc = {};
  l_Desc.nextInChain = nullptr;

  m_Instance = wgpuCreateInstance(&l_Desc);
  if (!m_Instance) {
    MYON_DO_CORE_ASSERT("Could not initialize WebGPU Instance!");
  }

  MYON_CORE_INFO("WebGPU Instance initialized!");
}

WebGPUInstance::~WebGPUInstance() {
  MYON_CORE_INFO("Releasing WebGPU Instance...");

  wgpuInstanceRelease(m_Instance);
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

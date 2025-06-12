// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUAPI::WebGPUAPI() {
  // WebGPU Instance
  m_WebGPUInstance = std::make_unique<WebGPUInstance>();

  // WebGPU Adapter
  m_WebGPUAdapterConfig = WebGPUAdapterConfig{
    .p_Instance = m_WebGPUInstance->getInstance()
  };
  m_WebGPUAdapter = std::make_unique<WebGPUAdapter>(m_WebGPUAdapterConfig);
}

WebGPUAPI::~WebGPUAPI() { MYON_CORE_INFO("Shutting down WebGPU..."); }
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

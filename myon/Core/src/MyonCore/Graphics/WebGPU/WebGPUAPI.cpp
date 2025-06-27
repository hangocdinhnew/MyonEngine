// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUAPI::WebGPUAPI(std::string &title) {
  // WebGPU Instance
  m_WebGPUInstance = std::make_unique<WebGPUInstance>();

  // WebGPU Adapter
  m_WebGPUAdapterConfig =
      WebGPUAdapterConfig{.p_Instance = m_WebGPUInstance->getInstance()};
  m_WebGPUAdapter = std::make_unique<WebGPUAdapter>(m_WebGPUAdapterConfig);

  // WebGPU Device
  m_WebGPUDeviceConfig = WebGPUDeviceConfig{
      .p_Name = title,
      .p_Adapter = m_WebGPUAdapter->getAdapter(),
  };
  m_WebGPUDevice = std::make_unique<WebGPUDevice>(m_WebGPUDeviceConfig);

  // WebGPU Command Queue
  m_WebGPUCommandQueueConfig =
      WebGPUCommandQueueConfig{.p_Device = m_WebGPUDevice->getDevice()};
  m_WebGPUCommandQueue =
      std::make_unique<WebGPUCommandQueue>(m_WebGPUCommandQueueConfig);
}

WebGPUAPI::~WebGPUAPI() { MYON_CORE_INFO("Shutting down WebGPU..."); }
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

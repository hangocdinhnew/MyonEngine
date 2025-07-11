// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Graphics/WebGPU/WebGPUAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
namespace WebGPU {
WebGPUAPI::WebGPUAPI(SDL_Window *m_Window, std::string &title) {
  // WebGPU Instance
  m_WebGPUInstance = std::make_unique<WebGPUInstance>();

  // WebGPU Surface
  m_WebGPUSurfaceConfig = WebGPUSurfaceConfig{
      .p_Instance = m_WebGPUInstance->getInstance(), .p_Window = m_Window};
  m_WebGPUSurface = std::make_unique<WebGPUSurface>(m_WebGPUSurfaceConfig);

  // WebGPU Adapter
  m_WebGPUAdapterConfig =
      WebGPUAdapterConfig{.p_Instance = m_WebGPUInstance->getInstance(),
                          .p_Surface = m_WebGPUSurface->getSurface()};
  m_WebGPUAdapter = std::make_unique<WebGPUAdapter>(m_WebGPUAdapterConfig);

  // WebGPU Device
  m_WebGPUDeviceConfig = WebGPUDeviceConfig{
      .p_Name = title,
      .p_Instance = m_WebGPUInstance->getInstance(),
      .p_Adapter = m_WebGPUAdapter->getAdapter(),
  };
  m_WebGPUDevice = std::make_unique<WebGPUDevice>(m_WebGPUDeviceConfig);

  // WebGPU Command Queue
  m_WebGPUCommandQueueConfig = WebGPUCommandQueueConfig{
      .p_Instance = m_WebGPUInstance->getInstance(),
      .p_Device = m_WebGPUDevice->getDevice()};
  m_WebGPUCommandQueue =
      std::make_unique<WebGPUCommandQueue>(m_WebGPUCommandQueueConfig);

  m_WebGPUSurface->configureSurface(m_WebGPUAdapter->getAdapter(),
                                    m_WebGPUDevice->getDevice());
}

WebGPUAPI::~WebGPUAPI() {
  MYON_CORE_INFO("Shutting down WebGPU...");

  m_WebGPUSurface->unconfigureSurface();
}
} // namespace WebGPU
} // namespace Graphics
} // namespace MyonCore

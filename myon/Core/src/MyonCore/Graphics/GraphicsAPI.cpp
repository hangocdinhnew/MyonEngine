// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Graphics {
GraphicsAPI::GraphicsAPI(SDL_Window *m_Window, std::string &title,
                         MyonRHI::GPUBackend p_Backend) {
  m_Backend = p_Backend;

  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPUAPI = std::make_unique<WebGPU::WebGPUAPI>(
        m_Window, title);

    break;
  default:
    MYON_DO_CORE_ASSERT("Invalid Graphics API!");
  }
}

MyonRHI::GPUDevice &GraphicsAPI::getDevice() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU: {
    WGPUDevice device = m_WebGPUAPI->getDevice();
    m_Device.webgpu.device = device;

    return m_Device;
  }

  default:
    MYON_DO_CORE_ASSERT("Invalid Graphics API!");
  }
}

MyonRHI::GPUQueue &GraphicsAPI::getQueue() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU: {
    WGPUQueue queue = m_WebGPUAPI->getQueue();
    m_Queue.webgpu.queue = queue;

    return m_Queue;
  }

  default:
    MYON_DO_CORE_ASSERT("Invalid Graphics API!");
  }
}

MyonRHI::GPUSurface &GraphicsAPI::getSurface() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU: {
    WGPUSurface surface = m_WebGPUAPI->getSurface();
    WGPUSurfaceCapabilities surfaceCapabilities =
        m_WebGPUAPI->getSurfaceCapabilities();
    WGPUSurfaceConfiguration surfaceConfiguration =
        m_WebGPUAPI->getSurfaceConfiguration();
    m_Surface.webgpu.surface = surface;
    m_Surface.webgpu.surfaceCapabilities = surfaceCapabilities;
    m_Surface.webgpu.surfaceConfig = surfaceConfiguration;

    return m_Surface;
  }

  default:
    MYON_DO_CORE_ASSERT("Invalid Graphics API!");
  }
}
} // namespace Graphics
} // namespace MyonCore

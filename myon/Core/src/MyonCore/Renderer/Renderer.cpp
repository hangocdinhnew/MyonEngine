// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Renderer/Renderer.hpp"
// clang-format on

namespace MyonCore {
namespace Renderer {

Renderer::Renderer(RendererConfig &p_RendererConfig)
    : m_Device(p_RendererConfig.p_Device),
      m_Surface(p_RendererConfig.p_Surface), m_Queue(p_RendererConfig.p_Queue),
      m_Backend(p_RendererConfig.p_Backend) {
  MYON_CORE_ASSERT(!m_Device.has_value(), "Failed to access m_Device!");
  MYON_CORE_ASSERT(!m_Surface.has_value(), "Failed to access m_Surface!");
  MYON_CORE_ASSERT(!m_Queue.has_value(), "Failed to access m_Queue!");

  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURendererConfig = {.p_Device = m_Device.value().webgpu.device,
                              .p_Queue = m_Queue.value().webgpu.queue,
                              .p_Surface = m_Surface.value().webgpu.surface,
                              .p_SurfaceCapabilities =
                                  m_Surface.value().webgpu.surfaceCapabilities};
    m_WebGPURenderer = std::make_unique<WebGPURenderer>(m_WebGPURendererConfig);
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::AcquireNextImage() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->AcquireNextImage();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::BeginCommandBuffer() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->BeginCommandBuffer();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::BeginRenderPass() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->BeginRenderPass();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::EndRenderPass() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->EndRenderPass();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::EndCommandBuffer() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->EndCommandBuffer();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::Submit() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->Submit();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::Present() {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->Present();
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

void Renderer::ClearColor(float r, float g, float b, float a) {
  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURenderer->ClearColor(r, g, b, a);
    break;

  default:
    MYON_DO_CORE_ASSERT("Renderer - Unknown or unsupported GPU backend");
    break;
  }
}

} // namespace Renderer
} // namespace MyonCore

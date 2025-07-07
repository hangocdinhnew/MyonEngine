// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Renderer/Renderer.hpp"
// clang-format on

namespace MyonCore {
namespace Renderer {

Renderer::Renderer(RendererConfig &p_RendererConfig)
    : m_Device(p_RendererConfig.p_GraphicsAPI->getDevice()),
      m_Surface(p_RendererConfig.p_GraphicsAPI->getSurface()),
      m_Queue(p_RendererConfig.p_GraphicsAPI->getQueue()),
      m_Backend(p_RendererConfig.p_Backend) {

  switch (m_Backend) {
  case MyonRHI::GPUBackend::WebGPU:
    m_WebGPURendererConfig = {.p_Device = m_Device.webgpu.device,
                              .p_Queue = m_Queue.webgpu.queue,
                              .p_Surface = m_Surface.webgpu.surface,
                              .p_SurfaceCapabilities =
                                  m_Surface.webgpu.surfaceCapabilities};
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

#pragma once

// clang-format off
#include <optional>

#include "MyonCore/RHI/RHI.hpp"
#include "MyonCore/Renderer/WebGPURenderer.hpp"
// clang-format on

namespace MyonCore {
namespace Renderer {
struct RendererConfig {
  MyonRHI::GPUBackend p_Backend;
  std::optional<MyonRHI::GPUDevice> p_Device;
  std::optional<MyonRHI::GPUQueue> p_Queue;
  std::optional<MyonRHI::GPUSurface> p_Surface;
};

class Renderer {
public:
  Renderer(RendererConfig &p_RendererConfig);
  ~Renderer() = default;

  void AcquireNextImage();
  void BeginCommandBuffer();
  void BeginRenderPass();
  void EndRenderPass();
  void EndCommandBuffer();
  void Submit();
  void Present();

  void ClearColor(float r, float g, float b, float a);

private:
  MyonRHI::GPUBackend m_Backend;
  std::optional<MyonRHI::GPUDevice> &m_Device;
  std::optional<MyonRHI::GPUQueue> &m_Queue;
  std::optional<MyonRHI::GPUSurface> &m_Surface;

  WebGPURendererConfig m_WebGPURendererConfig;
  std::unique_ptr<WebGPURenderer> m_WebGPURenderer;
};
} // namespace Renderer
} // namespace MyonCore

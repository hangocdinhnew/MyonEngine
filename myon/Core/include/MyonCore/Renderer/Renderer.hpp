#pragma once

// clang-format off
#include <memory>
#include <optional>

#include "MyonCore/RHI/RHI.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"
#include "MyonCore/Renderer/WebGPURenderer.hpp"
// clang-format on

namespace MyonCore {
namespace Renderer {
struct RendererConfig {
  MyonRHI::GPUBackend p_Backend;
  Graphics::GraphicsAPI* p_GraphicsAPI;
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
  MyonRHI::GPUDevice m_Device;
  MyonRHI::GPUQueue m_Queue;
  MyonRHI::GPUSurface m_Surface;

  WebGPURendererConfig m_WebGPURendererConfig;
  std::unique_ptr<WebGPURenderer> m_WebGPURenderer;
  Graphics::GraphicsAPI* m_GraphicsAPI;
};
} // namespace Renderer
} // namespace MyonCore

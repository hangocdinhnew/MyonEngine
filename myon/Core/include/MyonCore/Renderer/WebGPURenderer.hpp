#pragma once

// clang-format off
#include <optional>

#include <SDL3/SDL.h>
#include <webgpu/webgpu.h>
// clang-format on

namespace MyonCore {
namespace Renderer {
struct WebGPURendererConfig {
  std::optional<WGPUDevice> p_Device;
  std::optional<WGPUQueue> p_Queue;
  std::optional<WGPUSurface> p_Surface;
  std::optional<WGPUSurfaceCapabilities> p_SurfaceCapabilities;
  std::optional<WGPUSurfaceConfiguration> p_SurfaceConfig;
  std::optional<SDL_Window *> p_Window;
};

class WebGPURenderer {
public:
  WebGPURenderer(WebGPURendererConfig &p_RendererConfig);
  ~WebGPURenderer() = default;

  void ClearColor(float r, float g, float b, float a);

  void AcquireNextImage();
  void BeginCommandBuffer();
  void BeginRenderPass();
  void EndRenderPass();
  void EndCommandBuffer();
  void Submit();
  void Present();

private:
  std::optional<WGPUDevice> &m_Device;
  std::optional<WGPUQueue> &m_Queue;
  std::optional<WGPUSurface> &m_Surface;
  std::optional<WGPUSurfaceCapabilities> &m_SurfaceCapabilities;
  std::optional<WGPUSurfaceConfiguration> &m_SurfaceConfig;
  std::optional<SDL_Window *> &m_Window;

  void reconfigureSurface();

  WGPUSurfaceTexture m_SurfaceTexture;
  WGPUTextureView m_TargetView;
  WGPUCommandEncoder m_CommandEncoder;
  WGPURenderPassColorAttachment m_ColorAttachment;
  WGPURenderPassEncoder m_RenderPassEncoder;
  WGPUCommandBuffer m_CommandBuffer;

  WGPUColor m_ClearColor{1, 1, 1, 1};

  WGPUTextureView GetNextSurfaceView();
};
} // namespace Renderer
} // namespace MyonCore

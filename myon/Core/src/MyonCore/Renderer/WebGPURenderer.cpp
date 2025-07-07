// clang-format off
#include "MyonCore/Graphics/WebGPU/WebGPUUtils.hpp"
#include "MyonCore/Renderer/WebGPURenderer.hpp"
#include "MyonCore/Core/Log.hpp"
// clang-format on

namespace MyonCore {
namespace Renderer {
WebGPURenderer::WebGPURenderer(WebGPURendererConfig &p_RendererConfig)
    : m_Device(p_RendererConfig.p_Device), m_Queue(p_RendererConfig.p_Queue),
      m_Surface(p_RendererConfig.p_Surface),
      m_SurfaceCapabilities(p_RendererConfig.p_SurfaceCapabilities),
      m_SurfaceConfig(p_RendererConfig.p_SurfaceConfig),
      m_Window(p_RendererConfig.p_Window) {
  MYON_CORE_ASSERT(!m_Device.has_value(),
                   "WebGPU Renderer - Failed to access m_Device!");
  MYON_CORE_ASSERT(!m_Queue.has_value(),
                   "WebGPU Renderer - Failed to access m_Queue!");
  MYON_CORE_ASSERT(!m_Surface.has_value(),
                   "WebGPU Renderer - Failed to access m_Surface!");
  MYON_CORE_ASSERT(!m_SurfaceCapabilities.has_value(),
                   "WebGPU Renderer - Failed to access m_SurfaceCapabilities!");
  MYON_CORE_ASSERT(!m_SurfaceConfig.has_value(),
                   "WebGPU Renderer - Failed to access m_SurfaceConfig!");
  MYON_CORE_ASSERT(!m_Window.has_value(),
                   "WebGPU Renderer - Failed to access m_Window!");
}

void WebGPURenderer::ClearColor(float r, float g, float b, float a) {
  m_ClearColor = WGPUColor{r, g, b, a};
}

void WebGPURenderer::AcquireNextImage() {
  m_TargetView = GetNextSurfaceView();
  if (!m_TargetView)
    return;
}

void WebGPURenderer::BeginCommandBuffer() {
  WGPUCommandEncoderDescriptor encoderDesc = {};
  encoderDesc.label =
      Graphics::WebGPU::toWGPUStringView("Myon::CommandEncoder");
  m_CommandEncoder =
      wgpuDeviceCreateCommandEncoder(m_Device.value(), &encoderDesc);
}

void WebGPURenderer::BeginRenderPass() {
  m_ColorAttachment = {};
  m_ColorAttachment.view = m_TargetView;
  m_ColorAttachment.loadOp = WGPULoadOp_Clear;
  m_ColorAttachment.storeOp = WGPUStoreOp_Store;
  m_ColorAttachment.clearValue = m_ClearColor;

  WGPURenderPassDescriptor renderPassDesc = {};
  renderPassDesc.colorAttachmentCount = 1;
  renderPassDesc.colorAttachments = &m_ColorAttachment;

  m_RenderPassEncoder =
      wgpuCommandEncoderBeginRenderPass(m_CommandEncoder, &renderPassDesc);
}

void WebGPURenderer::EndRenderPass() {
  if (m_RenderPassEncoder) {
    wgpuRenderPassEncoderEnd(m_RenderPassEncoder);
    wgpuRenderPassEncoderRelease(m_RenderPassEncoder);
    m_RenderPassEncoder = nullptr;
  }
}

void WebGPURenderer::EndCommandBuffer() {
  WGPUCommandBufferDescriptor cmdBufferDesc = {};
  cmdBufferDesc.label =
      Graphics::WebGPU::toWGPUStringView("Myon::CommandBuffer");

  m_CommandBuffer = wgpuCommandEncoderFinish(m_CommandEncoder, &cmdBufferDesc);
  wgpuCommandEncoderRelease(m_CommandEncoder);
  m_CommandEncoder = nullptr;
}

void WebGPURenderer::Submit() {
  if (!m_CommandBuffer)
    return;
  wgpuQueueSubmit(m_Queue.value(), 1, &m_CommandBuffer);
  wgpuCommandBufferRelease(m_CommandBuffer);
  m_CommandBuffer = nullptr;
}

void WebGPURenderer::Present() {
  if (m_TargetView) {
    wgpuTextureViewRelease(m_TargetView);
    m_TargetView = nullptr;
  }

  wgpuSurfacePresent(m_Surface.value());
  wgpuTextureRelease(m_SurfaceTexture.texture);
}

WGPUTextureView WebGPURenderer::GetNextSurfaceView() {
  m_SurfaceTexture = {};
  wgpuSurfaceGetCurrentTexture(m_Surface.value(), &m_SurfaceTexture);

  if (m_SurfaceTexture.status !=
          WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
      m_SurfaceTexture.status !=
          WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {

    switch (m_SurfaceTexture.status) {
    case WGPUSurfaceGetCurrentTextureStatus_DeviceLost:
    case WGPUSurfaceGetCurrentTextureStatus_Error:
    case WGPUSurfaceGetCurrentTextureStatus_Lost:
    case WGPUSurfaceGetCurrentTextureStatus_OutOfMemory: {
      std::string statusStr =
          std::to_string(static_cast<int>(m_SurfaceTexture.status));
      MYON_DO_CORE_ASSERT("WebGPU - Surface failure with status {}!",
                          statusStr);
    }

    default:
      reconfigureSurface();
      break;
    }
  }

  WGPUTextureViewDescriptor viewDescriptor = {};
  viewDescriptor.label =
      Graphics::WebGPU::toWGPUStringView("Surface texture view");
  viewDescriptor.dimension = WGPUTextureViewDimension_2D;
  viewDescriptor.format = m_SurfaceCapabilities.value().formats[0];
  viewDescriptor.baseMipLevel = 0;
  viewDescriptor.mipLevelCount = 1;
  viewDescriptor.baseArrayLayer = 0;
  viewDescriptor.arrayLayerCount = 1;
  viewDescriptor.aspect = WGPUTextureAspect_All;

  WGPUTextureView targetView =
      wgpuTextureCreateView(m_SurfaceTexture.texture, &viewDescriptor);

  return targetView;
}

void WebGPURenderer::reconfigureSurface() {
  m_SurfaceConfig.value() = {};

  int width, height;
  SDL_GetWindowSize(m_Window.value(), &width, &height);

  m_SurfaceConfig.value().width = width;
  m_SurfaceConfig.value().height = height;
  m_SurfaceConfig.value().device = m_Device.value();

  m_SurfaceConfig.value().format = m_SurfaceCapabilities.value().formats[0];
  m_SurfaceConfig.value().usage = WGPUTextureUsage_RenderAttachment;

  m_SurfaceConfig.value().presentMode = WGPUPresentMode_Fifo;
  m_SurfaceConfig.value().alphaMode = WGPUCompositeAlphaMode_Auto;

  wgpuSurfaceConfigure(m_Surface.value(), &m_SurfaceConfig.value());
}
} // namespace Renderer
} // namespace MyonCore

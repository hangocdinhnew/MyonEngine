#include "MyonCore/Core/Engine.hpp"

namespace MyonCore {
namespace Core {
Engine::Engine(EngineInfo &engineInfo) {
  m_Log = std::make_unique<Core::Log>();

  m_Time = std::make_unique<Utils::Time>();

  m_Window = std::make_unique<Core::Window>(engineInfo.width, engineInfo.height,
                                            engineInfo.name);

  m_GraphicsAPI = std::make_unique<Graphics::GraphicsAPI>(
      m_Window->GetNativeWindow(), engineInfo.name,
      MyonRHI::GPUBackend::WebGPU);

  m_RendererConfig =
      Renderer::RendererConfig{.p_Backend = MyonRHI::GPUBackend::WebGPU,
                               .p_Device = m_GraphicsAPI->getDevice(),
                               .p_Queue = m_GraphicsAPI->getQueue(),
                               .p_Surface = m_GraphicsAPI->getSurface(),
                               .p_Window = m_Window->GetNativeWindow()};
  m_Renderer = std::make_unique<Renderer::Renderer>(m_RendererConfig);

  MYON_CORE_INFO("Engine initialized!");
}

Engine::~Engine() {
  for (Layers::Layer *layer : m_LayerStack) {
    PopLayer(layer);
  }

  MYON_CORE_INFO("All layers popped!");

  MYON_CORE_INFO("Engine shutting down...");
}

void Engine::PushLayer(Layers::Layer *layer) {
  m_LayerStack.PushLayer(layer);

  MYON_CORE_INFO("Layer pushed!");
}

void Engine::PushOverlay(Layers::Layer *layer) {
  m_LayerStack.PushOverlay(layer);

  MYON_CORE_INFO("Overlay pushed!");
}

void Engine::PopLayer(Layers::Layer *layer) { m_LayerStack.PopLayer(layer); }

void Engine::PopOverlay(Layers::Layer *layer) {
  m_LayerStack.PopOverlay(layer);
}

void Engine::Run() {
  while (IsRunning()) {
    m_Window->PollEvents();
    m_GraphicsAPI->PollDevice();
    Utils::Time::Update();

    float deltatime = Utils::Time::GetDeltaTime();
    for (Layers::Layer *layer : m_LayerStack)
      layer->OnUpdate(deltatime);

    m_Renderer->AcquireNextImage();
    m_Renderer->BeginCommandBuffer();
    m_Renderer->BeginRenderPass();

    for (Layers::Layer *layer : m_LayerStack)
      layer->OnRender();

    m_Renderer->EndRenderPass();
    m_Renderer->EndCommandBuffer();
    m_Renderer->Submit();
    m_Renderer->Present();
  }
}
} // namespace Core
} // namespace MyonCore

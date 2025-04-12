#include "MyonCore/Core/Engine.hpp"

namespace MyonCore {
Engine::Engine(EngineInfo *engineInfo) {
  m_Log = std::make_unique<Log>();

  m_Time = std::make_unique<Time>();

  m_Window = std::make_unique<Window>(engineInfo->width, engineInfo->height,
                                      engineInfo->title);

  m_GraphicsAPI = std::make_unique<GraphicsAPI>(
      m_Window->GetNativeWindow(), engineInfo->title, engineInfo->vert,
      engineInfo->frag);

  // Log
  MYON_CORE_INFO("Engine initialized!");
}

Engine::~Engine() {
  for (Layer *layer : m_LayerStack) {
    PopLayer(layer);
  }

  MYON_CORE_INFO("All layers popped!");

  MYON_CORE_INFO("Engine shutting down...");
}

void Engine::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);

  MYON_CORE_INFO("Layer pushed!");
}

void Engine::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);

  MYON_CORE_INFO("Overlay pushed!");
}

void Engine::PopLayer(Layer *layer) { m_LayerStack.PopLayer(layer); }

void Engine::PopOverlay(Layer *layer) { m_LayerStack.PopOverlay(layer); }

void Engine::Run() {
  while (IsRunning()) {
    if (m_GraphicsAPI->ShouldRecreateSwapChain()) {
      m_GraphicsAPI->RecreateSwapchain();
      continue;
    }

    m_GraphicsAPI->DrawFrame();

    Time::Update();

    float deltatime = MyonCore::Time::GetDeltaTime();
    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate(deltatime);
      layer->OnRender();
    }

    PollEvents();
  }

  m_GraphicsAPI->getLogicalDevice().waitIdle();
}

} // namespace MyonCore

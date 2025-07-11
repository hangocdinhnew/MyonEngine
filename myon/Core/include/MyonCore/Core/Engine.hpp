#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Utils/Time.hpp"
#include "MyonCore/Layers/LayerStack.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"
#include "MyonCore/Renderer/Renderer.hpp"
// clang-format on

namespace MyonCore {
namespace Core {

struct EngineInfo {
  int width;
  int height;
  std::string name;
};

class Engine {
public:
  Engine(EngineInfo &engineInfo);
  ~Engine();

  bool IsRunning() const { return m_Window->IsRunning(); }

  void Run();

  // Layers
  void PushLayer(Layers::Layer *layer);
  void PushOverlay(Layers::Layer *layer);

  void PopLayer(Layers::Layer *layer);
  void PopOverlay(Layers::Layer *layer);

  Graphics::GraphicsAPI *getGraphicsAPI() { return m_GraphicsAPI.get(); }
  Renderer::Renderer *getRenderer() { return m_Renderer.get(); }

private:
  std::unique_ptr<Core::Log> m_Log;
  std::unique_ptr<Utils::Time> m_Time;
  std::unique_ptr<Core::Window> m_Window;
  std::unique_ptr<Graphics::GraphicsAPI> m_GraphicsAPI;

  Renderer::RendererConfig m_RendererConfig;
  std::unique_ptr<Renderer::Renderer> m_Renderer;

  Layers::LayerStack m_LayerStack;
};
} // namespace Core
} // namespace MyonCore

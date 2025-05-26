#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Utils/Time.hpp"
#include "MyonCore/Layers/LayerStack.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"
// clang-format on

namespace MyonCore {
namespace Core {

struct EngineInfo {
  int width;
  int height;
  std::string title;
  std::string vert;
  std::string frag;
};

class Engine {
public:
  Engine(EngineInfo &engineInfo);
  ~Engine();

  bool IsRunning() const { return m_Window->IsRunning(); }

  void PollEvents() { m_Window->PollEvents(); }

  void Run();

  // Layers
  void PushLayer(Layers::Layer *layer);
  void PushOverlay(Layers::Layer *layer);

  void PopLayer(Layers::Layer *layer);
  void PopOverlay(Layers::Layer *layer);

  // Graphics
  void DrawFrame() { m_GraphicsAPI->DrawFrame(); }

private:
  std::unique_ptr<Core::Log> m_Log;
  std::unique_ptr<Utils::Time> m_Time;
  std::unique_ptr<Core::Window> m_Window;
  std::unique_ptr<Graphics::GraphicsAPI> m_GraphicsAPI;

  Layers::LayerStack m_LayerStack;
};
} // namespace Core
} // namespace MyonCore

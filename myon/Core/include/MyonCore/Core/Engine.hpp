#pragma once

// clang-format off
#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Utils/Time.hpp"
#include "MyonCore/Layers/LayerStack.hpp"
#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"
// clang-format on

namespace MyonCore {

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
  void PushLayer(Layer *layer);
  void PushOverlay(Layer *layer);

  void PopLayer(Layer *layer);
  void PopOverlay(Layer *layer);

  // Graphics
  void DrawFrame() { m_GraphicsAPI->DrawFrame(); }

private:
  std::unique_ptr<Log> m_Log;
  std::unique_ptr<Time> m_Time;
  std::unique_ptr<Window> m_Window;
  std::unique_ptr<GraphicsAPI> m_GraphicsAPI;

  LayerStack m_LayerStack;
};
} // namespace MyonCore

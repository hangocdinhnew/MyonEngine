#pragma once

#include "MyonCore/Core/Log.hpp"
#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Graphics/GraphicsAPI.hpp"

namespace MyonCore {
class Engine {
public:
  Engine(int width, int height, const std::string &title);
  ~Engine();

  bool IsRunning() const { return m_Window->IsRunning(); }

  void PollEvents() { m_Window->PollEvents(); }

private:
  std::unique_ptr<Log> m_Log;
  std::unique_ptr<Window> m_Window;
  std::unique_ptr<GraphicsAPI> m_GraphicsAPI;
};
} // namespace MyonCore

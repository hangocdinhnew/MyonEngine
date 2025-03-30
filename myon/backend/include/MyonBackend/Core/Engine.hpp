#pragma once

#include "MyonBackend/Core/Log.hpp"
#include "MyonBackend/Core/Window.hpp"

namespace MyonBackend {
class Engine {
public:
  Engine(int width, int height, const std::string &title);
  ~Engine();

  bool IsRunning() const { return m_Window->IsRunning(); }

  void PollEvents() { m_Window->PollEvents(); }

private:
  std::unique_ptr<Log> m_Log;
  std::unique_ptr<Window> m_Window;
};
} // namespace MyonBackend

#pragma once

#include "LOEBackend/Core/Log.hpp"
#include "LOEBackend/Core/Window.hpp"

namespace LOEBackend {
class Engine {
public:
  Engine(int width, int height, const std::string& title);
  ~Engine();

  bool IsRunning() const {
    return m_Window->IsRunning();
  }

  void PollEvents() {
    m_Window->PollEvents();
  }

  void SwapBuffers() {
    m_Window->SwapBuffers();
  }

private:
  std::unique_ptr<Log> m_Log;
  std::unique_ptr<Window> m_Window;
};
} // namespace LOEBackend

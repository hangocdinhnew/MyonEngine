#pragma once

#include "MyonBackend/Core/Log.hpp"
#include "MyonBackend/Core/Window.hpp"
#include "MyonBackend/Graphics/GraphicsAPI.hpp"

namespace MyonBackend {
class Engine {
public:
  Engine(int width, int height, const std::string &title);
  ~Engine();

  bool IsRunning() const { return m_Window->IsRunning(); }

  void PollEvents() { m_Window->PollEvents(); }

private:
  Log *m_Log;
  Window *m_Window;
  GraphicsAPI* m_GraphicsAPI;
};
} // namespace MyonBackend

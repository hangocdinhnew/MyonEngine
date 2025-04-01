#include "MyonBackend/Core/Engine.hpp"

namespace MyonBackend {
Engine::Engine(int width, int height, const std::string &title) {
  m_Log = new Log();

  m_Window = new Window(width, height, title);

  m_GraphicsAPI = new GraphicsAPI(title);

  // Log
  MYON_CORE_INFO("Engine initialized!");
}

Engine::~Engine() {
  MYON_CORE_INFO("Engine shutting down...");
  delete m_GraphicsAPI;
  delete m_Window;
  delete m_Log;
}
} // namespace MyonBackend

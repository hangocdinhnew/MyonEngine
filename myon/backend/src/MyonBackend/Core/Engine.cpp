#include "MyonBackend/Core/Engine.hpp"

namespace MyonBackend {
Engine::Engine(int width, int height, const std::string &title) {
  m_Log = std::make_unique<Log>();

  m_Window = std::make_unique<Window>(width, height, title);

  m_GraphicsAPI = std::make_unique<GraphicsAPI>(title);

  // Log
  MYON_CORE_INFO("Engine initialized!");
}

Engine::~Engine() {
  MYON_CORE_INFO("Engine shutting down...");
}
} // namespace MyonBackend

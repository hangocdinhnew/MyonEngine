#include "MyonBackend/Core/Engine.hpp"

namespace MyonBackend {
Engine::Engine(int width, int height, const std::string& title) {
  m_Log = std::make_unique<Log>();

  // Log
  Myon_CORE_INFO("Engine initialized!");

  m_Window = std::make_unique<Window>(width, height, title);
}

Engine::~Engine() {
  Myon_CORE_INFO("Engine shutting down...");
}
}

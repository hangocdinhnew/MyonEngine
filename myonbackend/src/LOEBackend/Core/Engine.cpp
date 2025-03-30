#include "LOEBackend/Core/Engine.hpp"

namespace LOEBackend {
Engine::Engine(int width, int height, const std::string& title) {
  m_Log = std::make_unique<Log>();

  // Log
  LOE_CORE_INFO("Engine initialized!");

  m_Window = std::make_unique<Window>(width, height, title);
}

Engine::~Engine() {
  LOE_CORE_INFO("Engine shutting down...");
}
}

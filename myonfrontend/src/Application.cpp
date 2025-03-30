#include "LOEBackend/Core/Engine.hpp"

int main() {
  LOEBackend::Engine engine{600, 400, "lol"};

  while (engine.IsRunning()) {
    engine.PollEvents();
    engine.SwapBuffers();
  }

  return 0;
}

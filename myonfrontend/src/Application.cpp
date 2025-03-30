#include "MyonBackend/Core/Engine.hpp"

int main() {
  MyonBackend::Engine engine{600, 400, "lol"};

  while (engine.IsRunning()) {
    engine.PollEvents();
  }

  return 0;
}

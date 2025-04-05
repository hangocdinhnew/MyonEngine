#include "MyonCore/Core/Engine.hpp"

int main() {
  MyonCore::Engine engine{600, 400, "lol"};

  while (engine.IsRunning()) {
    engine.PollEvents();
  }

  return 0;
}

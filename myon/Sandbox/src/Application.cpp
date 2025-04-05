#include "MyonCore/Core/Engine.hpp"

class SandboxLayer : public MyonCore::Layer {
public:
  SandboxLayer() : MyonCore::Layer("Sandbox Layer") {}

  void OnAttach() override {}
  void OnDetach() override {}
  void OnUpdate(float deltatime) override {}
};

int main() {
  MyonCore::Engine engine{600, 400, "lol"};

  engine.PushLayer(new SandboxLayer);
  engine.Run();

  return 0;
}

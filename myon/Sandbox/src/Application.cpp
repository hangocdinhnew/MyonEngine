#include "MyonCore/Core/Engine.hpp"

class SandboxLayer : public MyonCore::Layer {
public:
  SandboxLayer() : MyonCore::Layer("Sandbox Layer") {}

  void OnAttach() override {}
  void OnDetach() override {}
  void OnUpdate(float deltatime) override {}
};

int main() {
  MyonCore::EngineInfo engineInfo{};
  engineInfo.width = 800;
  engineInfo.height = 600;
  engineInfo.title = "Lol";
  engineInfo.vert = "assets/Shaders/vertshader.vert";
  engineInfo.frag = "assets/Shaders/fragshader.frag";

  MyonCore::Engine engine{&engineInfo};

  engine.PushLayer(new SandboxLayer);
  engine.Run();

  return 0;
}

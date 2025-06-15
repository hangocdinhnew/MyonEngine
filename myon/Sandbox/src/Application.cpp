#include "MyonCore/Core/Engine.hpp"

class SandboxLayer : public MyonCore::Layers::Layer {
public:
  SandboxLayer() : MyonCore::Layers::Layer("Sandbox Layer") {}

  void OnAttach() override {}
  void OnDetach() override {}
  void OnUpdate(float deltatime) override {}
  void OnRender() override {}
};

int main() {
  MyonCore::Core::EngineInfo engineInfo{};
  engineInfo.width = 800;
  engineInfo.height = 600;
  engineInfo.name = "Lol";
  engineInfo.vert = "assets/Shaders/vertshader.vert";
  engineInfo.frag = "assets/Shaders/fragshader.frag";

  MyonCore::Core::Engine engine{engineInfo};

  engine.PushLayer(new SandboxLayer);
  engine.Run();

  return 0;
}

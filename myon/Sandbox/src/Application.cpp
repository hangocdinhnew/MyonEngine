#include "MyonCore/Core/Engine.hpp"

class SandboxLayer : public MyonCore::Layers::Layer {
public:
  SandboxLayer(MyonCore::Renderer::Renderer *p_Renderer)
      : MyonCore::Layers::Layer("Sandbox Layer"), m_Renderer(p_Renderer) {}

  void OnAttach() override {}
  void OnDetach() override {}
  void OnUpdate(float deltatime) override {}
  void OnRender() override {}

private:
  MyonCore::Renderer::Renderer *m_Renderer;
};

int main() {
  MyonCore::Core::EngineInfo engineInfo{};
  engineInfo.width = 800;
  engineInfo.height = 600;
  engineInfo.name = "Lol";
  engineInfo.computeFolderName = "MyonSandbox";
  engineInfo.computeFileName = "computeshader.wgsl";

  MyonCore::Core::Engine engine{engineInfo};
  auto *gfx = engine.getGraphicsAPI();
  auto *renderer = engine.getRenderer();
  gfx->FetchComputeBufferDataSync();

  engine.PushLayer(new SandboxLayer(renderer));
  engine.Run();

  return 0;
}

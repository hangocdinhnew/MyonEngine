#pragma once

#include <string>

namespace MyonCore {

class Layer {
public:
  Layer(const std::string &name = "Layer") : m_DebugName(name) {}
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}

  const std::string &GetName() const { return m_DebugName; }

protected:
  std::string m_DebugName;
};

} // namespace MyonCore

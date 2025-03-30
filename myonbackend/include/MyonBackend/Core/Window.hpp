#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <string>

namespace MyonBackend {
class Window {
public:
  Window(int width, int height, const std::string &title);
  ~Window();

  bool IsRunning() const;
  void PollEvents();
  void SwapBuffers();

private:
  GLFWwindow *m_Window;
};
} // namespace MyonBackend

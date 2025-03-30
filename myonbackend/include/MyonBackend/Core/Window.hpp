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

private:
  void initWindow(int width, int height, const std::string &title);
  void cleanupWindow();

  GLFWwindow *m_Window;
};
} // namespace MyonBackend

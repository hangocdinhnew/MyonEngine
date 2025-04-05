#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Core/Log.hpp"

namespace MyonCore {
Window::Window(int width, int height, const std::string &title) {
  initWindow(width, height, title);
}

Window::~Window() {
  cleanupWindow();
}

void Window::initWindow(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    MYON_DO_CORE_ASSERT("Request to init GLFW was failed.");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_Window) {
    MYON_ERROR("Request to create the window was failed.");
    glfwTerminate();
    std::abort();
  }

  MYON_CORE_INFO("Requested window ({}x{}) created successfully!", width,
                 height);
}

void Window::cleanupWindow() {
  MYON_INFO("Terminating window...");
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

bool Window::IsRunning() const { return !glfwWindowShouldClose(m_Window); }

void Window::PollEvents() { glfwPollEvents(); }

} // namespace MyonCore

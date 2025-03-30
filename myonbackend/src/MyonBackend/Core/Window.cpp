#include "MyonBackend/Core/Window.hpp"
#include "MyonBackend/Core/Log.hpp"

namespace MyonBackend {
Window::Window(int width, int height, const std::string &title) {
  initWindow(width, height, title);
}

Window::~Window() { cleanupWindow(); }

void Window::initWindow(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    Myon_CORE_ERROR("Request to init GLFW was failed.");
    std::terminate();
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_Window) {
    Myon_ERROR("Request to create the window was failed.");
    glfwTerminate();
    std::terminate();
  }

  Myon_CORE_INFO("Requested window ({}x{}) created successfully!", width,
                 height);
}

void Window::cleanupWindow() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
  Myon_INFO("Window terminated.");
}

bool Window::IsRunning() const { return !glfwWindowShouldClose(m_Window); }

void Window::PollEvents() { glfwPollEvents(); }

} // namespace MyonBackend

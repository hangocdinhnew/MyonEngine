#include "LOEBackend/Core/Window.hpp"
#include "LOEBackend/Core/Log.hpp"

namespace LOEBackend {
Window::Window(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    LOE_CORE_ERROR("Request to init GLFW was failed.");
    std::terminate();
  }

  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_Window) {
    LOE_ERROR("Request to create the window was failed.");
    glfwTerminate();
    std::terminate();
  }

  LOE_CORE_INFO("Requested window ({}x{}) created successfully!", width, height);
}

Window::~Window() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
  LOE_INFO("Window terminated.");
}

bool Window::IsRunning() const {
  return !glfwWindowShouldClose(m_Window);
}

void Window::PollEvents() {
  glfwPollEvents();
}

void Window::SwapBuffers() {
  glfwSwapBuffers(m_Window);
}

} // namespace LOEBackend

#include "MyonBackend/Core/Window.hpp"
#include "MyonBackend/Core/Log.hpp"

namespace MyonBackend {
Window::Window(int width, int height, const std::string &title) {
  initWindow(width, height, title);
  m_vkInstance = new VulkanInstance(title);
}

Window::~Window() {
  delete m_vkInstance;
  cleanupWindow();
}

void Window::initWindow(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    MYON_CORE_ERROR("Request to init GLFW was failed.");
    std::terminate();
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_Window) {
    MYON_ERROR("Request to create the window was failed.");
    glfwTerminate();
    std::terminate();
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

} // namespace MyonBackend

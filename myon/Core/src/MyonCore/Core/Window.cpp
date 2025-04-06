#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Core/Log.hpp"

namespace MyonCore {
Window::Window(int width, int height, const std::string &title) {
  initWindow(width, height, title);
}

Window::~Window() { cleanupWindow(); }

void Window::initWindow(int width, int height, const std::string &title) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    MYON_DO_CORE_ASSERT("SDL_Init failed: {}", SDL_GetError());
  }

  m_Window = SDL_CreateWindow(title.c_str(), width, height,
                              SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

  if (!m_Window) {
    MYON_CORE_ERROR("Failed to create the requested SDL3 Window: {}",
                    SDL_GetError());
    SDL_Quit();
    std::abort();
  }

  MYON_CORE_INFO("Requested window ({}x{}) created successfully!", width,
                 height);
}

void Window::cleanupWindow() {
  MYON_INFO("Terminating window...");
  if (m_Window) {
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
  }

  SDL_Quit();
}

bool Window::IsRunning() const { return m_IsRunning; }

void Window::PollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      m_IsRunning = false;
      break;
    }
  }
}

SDL_Window *Window::GetNativeWindow() const { return m_Window; }

} // namespace MyonCore

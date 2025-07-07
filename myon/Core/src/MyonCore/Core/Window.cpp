#include "MyonCore/Core/Window.hpp"
#include "MyonCore/Core/Log.hpp"

namespace MyonCore {
namespace Core {
Window::Window(int width, int height, const std::string &title) {
  initWindow(width, height, title);
}

Window::~Window() { cleanupWindow(); }

static void customSDLLogger(void*, int category, SDL_LogPriority priority, const char* message) {
  MYON_CORE_DEBUG("SDL Debug Message (category: {}, priority: {}) - {}", category, static_cast<int>(priority), message);
}

void Window::initWindow(int width, int height, const std::string &title) {
  SDL_LogOutputFunction(customSDLLogger);
  SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);

  MYON_CORE_ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL - SDL_Init failed: {}",
                   SDL_GetError());

  m_Window =
      SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);

  if (!m_Window) {
    MYON_CORE_ERROR("SDL - Failed to create the requested SDL3 Window: {}",
                    SDL_GetError());
    SDL_Quit();
    std::abort();
  }

  MYON_CORE_INFO("SDL - Requested SDL3 window ({}x{}) created successfully!",
                 width, height);
}

void Window::cleanupWindow() {
  MYON_INFO("SDL - Window requested to be terminated...");

  if (m_Window) {
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
  }
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
} // namespace Core
} // namespace MyonCore

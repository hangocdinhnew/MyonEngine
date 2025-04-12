#pragma once

// clang-format off
#include <memory>
#include <string>
#include <SDL3/SDL.h>
// clang-format on

namespace MyonCore {
class Window {
public:
  Window(int width, int height, const std::string &title);
  ~Window();

  bool IsRunning() const;
  void PollEvents();

  SDL_Window *GetNativeWindow() const;

  bool WasResized() const { return m_IsResized; }
  void ResetResizeFlag() { m_IsResized = false; }

private:
  void initWindow(int width, int height, const std::string &title);
  void cleanupWindow();

  SDL_Window *m_Window = nullptr;
  bool m_IsRunning = true;

  bool m_IsResized = true;
};
} // namespace MyonCore


#pragma once

#include <chrono>

namespace MyonCore {
namespace Utils {
class Time {
public:
  Time() { m_LastTime = std::chrono::high_resolution_clock::now(); }
  ~Time() = default;

  static void Update() {
    auto now = std::chrono::high_resolution_clock::now();
    m_DeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(
                      now - m_LastTime)
                      .count();
    m_LastTime = now;
  }

  static float GetDeltaTime() { return m_DeltaTime; }

private:
  static inline std::chrono::high_resolution_clock::time_point m_LastTime;
  static inline float m_DeltaTime = 0.0f;
};
} // namespace Utils
} // namespace MyonCore

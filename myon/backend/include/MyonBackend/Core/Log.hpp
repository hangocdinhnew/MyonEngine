#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace MyonBackend {
class Log {
public:
  Log();
  ~Log();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
} // namespace MyonBackend

// Core log macros
#define MYON_CORE_TRACE(...)                                                   \
  ::MyonBackend::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MYON_CORE_INFO(...)                                                    \
  ::MyonBackend::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MYON_CORE_WARN(...)                                                    \
  ::MyonBackend::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MYON_CORE_ERROR(...)                                                   \
  ::MyonBackend::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MYON_CORE_CRITICAL(...)                                                \
  ::MyonBackend::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MYON_TRACE(...)                                                        \
  ::MyonBackend::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MYON_INFO(...) ::MyonBackend::Log::GetClientLogger()->info(__VA_ARGS__)
#define MYON_WARN(...) ::MyonBackend::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MYON_ERROR(...)                                                        \
  ::MyonBackend::Log::GetClientLogger()->error(__VA_ARGS__)
#define MYON_CRITICAL(...)                                                     \
  ::MyonBackend::Log::GetClientLogger()->critical(__VA_ARGS__)

// Assert
#define MYON_DO_CORE_ASSERT(...)                                               \
  do {                                                                         \
    ::MyonBackend::Log::GetCoreLogger()->error(__VA_ARGS__);                   \
    std::abort();                                                              \
  } while (0)

#define MYON_DO_ASSERT(...)                                                    \
  do {                                                                         \
    ::MyonBackend::Log::GetClientLogger()->error(__VA_ARGS__);                 \
    std::abort();                                                              \
  } while (0)

#define MYON_CORE_ASSERT(condition, ...)                                       \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonBackend::Log::GetCoreLogger()->error(__VA_ARGS__);                 \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

#define MYON_ASSERT(condition, ...)                                            \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonBackend::Log::GetClientLogger()->error(__VA_ARGS__);               \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

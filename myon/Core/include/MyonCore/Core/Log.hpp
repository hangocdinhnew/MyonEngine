#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace MyonCore {
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
} // namespace MyonCore

// Core log macros
#define MYON_CORE_TRACE(...)                                                   \
  ::MyonCore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MYON_CORE_INFO(...) ::MyonCore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MYON_CORE_WARN(...) ::MyonCore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MYON_CORE_ERROR(...)                                                   \
  ::MyonCore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MYON_CORE_CRITICAL(...)                                                \
  ::MyonCore::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MYON_TRACE(...) ::MyonCore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MYON_INFO(...) ::MyonCore::Log::GetClientLogger()->info(__VA_ARGS__)
#define MYON_WARN(...) ::MyonCore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MYON_ERROR(...) ::MyonCore::Log::GetClientLogger()->error(__VA_ARGS__)
#define MYON_CRITICAL(...)                                                     \
  ::MyonCore::Log::GetClientLogger()->critical(__VA_ARGS__)

// Assert
#define MYON_DO_CORE_ASSERT(...)                                               \
  do {                                                                         \
    ::MyonCore::Log::GetCoreLogger()->error(__VA_ARGS__);                      \
    std::abort();                                                              \
  } while (0)

#define MYON_DO_ASSERT(...)                                                    \
  do {                                                                         \
    ::MyonCore::Log::GetClientLogger()->error(__VA_ARGS__);                    \
    std::abort();                                                              \
  } while (0)

#define MYON_CORE_ASSERT(condition, ...)                                       \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonCore::Log::GetCoreLogger()->error(__VA_ARGS__);                    \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

#define MYON_ASSERT(condition, ...)                                            \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonCore::Log::GetClientLogger()->error(__VA_ARGS__);                  \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace MyonCore {
namespace Core {
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
} // namespace Core
} // namespace MyonCore

// Core log macros
#define MYON_CORE_TRACE(...)                                                   \
  ::MyonCore::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MYON_CORE_INFO(...)                                                    \
  ::MyonCore::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MYON_CORE_WARN(...)                                                    \
  ::MyonCore::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MYON_CORE_ERROR(...)                                                   \
  ::MyonCore::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MYON_CORE_CRITICAL(...)                                                \
  ::MyonCore::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MYON_TRACE(...) ::MyonCore::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MYON_INFO(...) ::MyonCore::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define MYON_WARN(...) ::MyonCore::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MYON_ERROR(...) ::MyonCore::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define MYON_CRITICAL(...)                                                     \
  ::MyonCore::Core::Log::GetClientLogger()->critical(__VA_ARGS__)

// Assert
#define MYON_DO_CORE_ASSERT(...)                                               \
  do {                                                                         \
    ::MyonCore::Core::Log::GetCoreLogger()->error(__VA_ARGS__);                \
    std::abort();                                                              \
  } while (0)

#define MYON_DO_ASSERT(...)                                                    \
  do {                                                                         \
    ::MyonCore::Core::Log::GetClientLogger()->error(__VA_ARGS__);              \
    std::abort();                                                              \
  } while (0)

#define MYON_CORE_ASSERT(condition, ...)                                       \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonCore::Core::Log::GetCoreLogger()->error(__VA_ARGS__);              \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

#define MYON_ASSERT(condition, ...)                                            \
  do {                                                                         \
    if (!(condition)) {                                                        \
      ::MyonCore::Core::Log::GetClientLogger()->error(__VA_ARGS__);            \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

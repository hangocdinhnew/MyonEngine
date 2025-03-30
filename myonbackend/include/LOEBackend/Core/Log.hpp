#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace LOEBackend {
class Log {
public:
  Log();
  ~Log() = default;

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
} // namespace LOEBackend

// Core log macros
#define LOE_CORE_TRACE(...) ::LOEBackend::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOE_CORE_INFO(...) ::LOEBackend::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOE_CORE_WARN(...) ::LOEBackend::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOE_CORE_ERROR(...) ::LOEBackend::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOE_CORE_CRITICAL(...)                                                  \
  ::LOEBackend::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOE_TRACE(...) ::LOEBackend::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOE_INFO(...) ::LOEBackend::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOE_WARN(...) ::LOEBackend::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOE_ERROR(...) ::LOEBackend::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOE_CRITICAL(...) ::LOEBackend::Log::GetClientLogger()->critical(__VA_ARGS__)

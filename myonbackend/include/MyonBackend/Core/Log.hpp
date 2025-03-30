#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace MyonBackend {
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
} // namespace MyonBackend

// Core log macros
#define Myon_CORE_TRACE(...) ::MyonBackend::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define Myon_CORE_INFO(...) ::MyonBackend::Log::GetCoreLogger()->info(__VA_ARGS__)
#define Myon_CORE_WARN(...) ::MyonBackend::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define Myon_CORE_ERROR(...) ::MyonBackend::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Myon_CORE_CRITICAL(...)                                                  \
  ::MyonBackend::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define Myon_TRACE(...) ::MyonBackend::Log::GetClientLogger()->trace(__VA_ARGS__)
#define Myon_INFO(...) ::MyonBackend::Log::GetClientLogger()->info(__VA_ARGS__)
#define Myon_WARN(...) ::MyonBackend::Log::GetClientLogger()->warn(__VA_ARGS__)
#define Myon_ERROR(...) ::MyonBackend::Log::GetClientLogger()->error(__VA_ARGS__)
#define Myon_CRITICAL(...) ::MyonBackend::Log::GetClientLogger()->critical(__VA_ARGS__)

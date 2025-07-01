// clang-format off
#include "MyonCore/Core/Log.hpp"

#ifdef MYON_LOGTOFILE
#include <spdlog/sinks/basic_file_sink.h>
#endif

#include <spdlog/sinks/stdout_color_sinks.h>
// clang-format on

namespace MyonCore {
namespace Core {
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

Log::Log() {
  std::vector<spdlog::sink_ptr> logSinks;
  logSinks.emplace_back(
      std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

#ifdef MYON_LOGTOFILE
  logSinks.emplace_back(
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("Myon.log", true));
#endif

  logSinks[0]->set_pattern("%^[%T] %n: %v%$");
#ifdef MYON_LOGTOFILE
  logSinks[1]->set_pattern("[%T] [%l] %n: %v");
#endif

  s_CoreLogger =
      std::make_shared<spdlog::logger>("Myon", begin(logSinks), end(logSinks));
  spdlog::register_logger(s_CoreLogger);
  s_CoreLogger->set_level(spdlog::level::trace);
  s_CoreLogger->flush_on(spdlog::level::trace);

  s_ClientLogger =
      std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
  spdlog::register_logger(s_ClientLogger);
  s_ClientLogger->set_level(spdlog::level::trace);
  s_ClientLogger->flush_on(spdlog::level::trace);

  MYON_CORE_INFO("Log system initialized!");
}

Log::~Log() { MYON_CORE_INFO("Log system shutting down..."); }
} // namespace Core
} // namespace MyonCore

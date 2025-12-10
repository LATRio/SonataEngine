#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Sonata
{

Ref<spdlog::logger> Log::s_EngineLogger;
Ref<spdlog::logger> Log::s_AppLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_EngineLogger = spdlog::stdout_color_mt("SONATA");
    s_EngineLogger->set_level(spdlog::level::trace);

    s_AppLogger = spdlog::stdout_color_mt("APP");
    s_AppLogger->set_level(spdlog::level::trace);

    SN_ENGINE_INFO("Logger Initialized! (powered by spdlog-{}.{}.{})", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR,
                   SPDLOG_VER_PATCH);
}

spdlog::logger *Log::GetEngineLogger()
{
    return s_EngineLogger.get();
}

spdlog::logger *Log::GetAppLogger()
{
    return s_AppLogger.get();
}

} // namespace Sonata

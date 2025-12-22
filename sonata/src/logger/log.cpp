#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#ifdef _MSC_VER
#include <spdlog/sinks/msvc_sink.h>
#endif

namespace Sonata {

Ref<spdlog::logger> Log::s_EngineLogger;
Ref<spdlog::logger> Log::s_AppLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_EngineLogger = spdlog::stdout_color_mt("SONATA");
#ifdef _MSC_VER
    s_EngineLogger->sinks().push_back(CreateRef<spdlog::sinks::msvc_sink_mt>());
#endif
    s_EngineLogger->set_level(spdlog::level::trace);

    s_AppLogger = spdlog::stdout_color_mt("APP");
#ifdef _MSC_VER
    s_EngineLogger->sinks().push_back(CreateRef<spdlog::sinks::msvc_sink_mt>());
#endif
    s_AppLogger->set_level(spdlog::level::trace);

    SN_ENGINE_INFO(
        "Logger Initialized! (powered by spdlog-{}.{}.{})", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
}

} // namespace Sonata

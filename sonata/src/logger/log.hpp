#pragma once
#include <spdlog/spdlog.h>
#include <signal.h>

namespace Sonata
{

typedef std::shared_ptr<spdlog::logger> LoggerPtr;

class Log
{
  public:
    static void Init();

    static spdlog::logger* GetEngineLogger();
    static spdlog::logger* GetAppLogger();

  private:
    static LoggerPtr s_EngineLogger;
    static LoggerPtr s_AppLogger;
};

} // namespace Sonata

#ifdef __linux__
#define DebugBreak() raise(SIGTRAP)
#elif _WIN32
#define DebugBreak() __debugbreak()
#else
#define DebugBreak()
#endif

#define SN_ENGINE_WARN(...) Sonata::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define SN_ENGINE_INFO(...) Sonata::Log::GetEngineLogger()->info(__VA_ARGS__)
#define SN_ENGINE_ERR(...) Sonata::Log::GetEngineLogger()->error(__VA_ARGS__); DebugBreak()
#define SN_ENGINE_TRACE(...) Sonata::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define SN_ENGINE_FATAL(...) Sonata::Log::GetEngineLogger()->critical(__VA_ARGS__); DebugBreak(); exit(999)
#define SN_APP_WARN(...) Sonata::Log::GetAppLogger()->warn(__VA_ARGS__)
#define SN_APP_INFO(...) Sonata::Log::GetAppLogger()->info(__VA_ARGS__)
#define SN_APP_ERR(...) Sonata::Log::GetAppLogger()->error(__VA_ARGS__); DebugBreak()
#define SN_APP_TRACE(...) Sonata::Log::GetAppLogger()->trace(__VA_ARGS__)
#define SN_APP_FATAL(...) Sonata::Log::GetAppLogger()->critical(__VA_ARGS__); DebugBreak(); exit(999)

#ifdef NDEBUG
#define SN_ENGINE_DEBUG(...)
#define SN_APP_DEBUG(...)
#else
#define SN_ENGINE_DEBUG(...) Sonata::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define SN_APP_DEBUG(...) Sonata::Log::GetAppLogger()->debug(__VA_ARGS__)
#endif

#pragma once
#include <spdlog/spdlog.h>

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

#define SN_ENGINE_WARN(...) Sonata::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define SN_ENGINE_INFO(...) Sonata::Log::GetEngineLogger()->info(__VA_ARGS__)
#define SN_ENGINE_ERR(...) Sonata::Log::GetEngineLogger()->error(__VA_ARGS__)
#define SN_ENGINE_TRACE(...) Sonata::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define SN_ENGINE_FATAL(...) Sonata::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define SN_APP_WARN(...) Sonata::Log::GetAppLogger()->warn(__VA_ARGS__)
#define SN_APP_INFO(...) Sonata::Log::GetAppLogger()->info(__VA_ARGS__)
#define SN_APP_ERR(...) Sonata::Log::GetAppLogger()->error(__VA_ARGS__)
#define SN_APP_TRACE(...) Sonata::Log::GetAppLogger()->trace(__VA_ARGS__)
#define SN_APP_FATAL(...) Sonata::Log::GetAppLogger()->critical(__VA_ARGS__)

#ifdef SONATA_DEBUG
#define SN_ENGINE_DEBUG(...) Sonata::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define SN_APP_DEBUG(...) Sonata::Log::GetAppLogger()->debug(__VA_ARGS__)
#else
#define SN_ENGINE_DEBUG(...)
#define SN_APP_DEBUG(...)
#endif



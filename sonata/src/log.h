#pragma once
#include <spdlog/spdlog.h>

namespace Sonata
{

enum class LoggerType
{
    Engine,
    App,
};

class Log
{
  public:
    static void Init();

    template <typename... Args>
    static void Warn(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args);
    template <typename... Args>
    static void Info(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args);
    template <typename... Args>
    static void Error(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args);
    template <typename... Args>
    static void Trace(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args);
    template <typename... Args>
    static void Fatal(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args);

  private:
    static std::shared_ptr<spdlog::logger> s_EngineLogger;
    static std::shared_ptr<spdlog::logger> s_AppLogger;
};

template <typename... Args>
void Log::Warn(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    switch (p_Type)
    {
    case LoggerType::Engine:
        s_EngineLogger->warn(fmt, std::forward<Args>(args)...);
        break;
    case LoggerType::App:
        s_AppLogger->warn(fmt, std::forward<Args>(args)...);
        break;
    default:
        break;
    }
}

template <typename... Args>
void Log::Info(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    switch (p_Type)
    {
    case LoggerType::Engine:
        s_EngineLogger->info(fmt, std::forward<Args>(args)...);
        break;
    case LoggerType::App:
        s_AppLogger->info(fmt, std::forward<Args>(args)...);
        break;
    default:
        break;
    }
}

template <typename... Args>
void Log::Error(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    switch (p_Type)
    {
    case LoggerType::Engine:
        s_EngineLogger->error(fmt, std::forward<Args>(args)...);
        break;
    case LoggerType::App:
        s_AppLogger->error(fmt, std::forward<Args>(args)...);
        break;
    default:
        break;
    }
}

template <typename... Args>
void Log::Trace(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    switch (p_Type)
    {
    case LoggerType::Engine:
        s_EngineLogger->trace(fmt, std::forward<Args>(args)...);
        break;
    case LoggerType::App:
        s_AppLogger->trace(fmt, std::forward<Args>(args)...);
        break;
    default:
        break;
    }
}

template <typename... Args>
void Log::Fatal(LoggerType p_Type, spdlog::format_string_t<Args...> fmt, Args &&...args)
{
    switch (p_Type)
    {
    case LoggerType::Engine:
        s_EngineLogger->critical(fmt, std::forward<Args>(args)...);
        break;
    case LoggerType::App:
        s_AppLogger->critical(fmt, std::forward<Args>(args)...);
        break;
    default:
        break;
    }
}

} // namespace Sonata

#define SN_ENGINE_WARN(...) Sonata::Log::Warn(Sonata::LoggerType::Engine, __VA_ARGS__)
#define SN_ENGINE_INFO(...) Sonata::Log::Info(Sonata::LoggerType::Engine, __VA_ARGS__)
#define SN_ENGINE_ERR(...) Sonata::Log::Error(Sonata::LoggerType::Engine, __VA_ARGS__)
#define SN_ENGINE_TRACE(...) Sonata::Log::Trace(Sonata::LoggerType::Engine, __VA_ARGS__)
#define SN_ENGINE_FATAL(...) Sonata::Log::Fatal(Sonata::LoggerType::Engine, __VA_ARGS__)
#define SN_APP_WARN(...) Sonata::Log::Warn(Sonata::LoggerType::App, __VA_ARGS__)
#define SN_APP_INFO(...) Sonata::Log::Info(Sonata::LoggerType::App, __VA_ARGS__)
#define SN_APP_ERR(...) Sonata::Log::Error(Sonata::LoggerType::App, __VA_ARGS__)
#define SN_APP_TRACE(...) Sonata::Log::Trace(Sonata::LoggerType::App, __VA_ARGS__)
#define SN_APP_FATAL(...) Sonata::Log::Fatal(Sonata::LoggerType::App, __VA_ARGS__)


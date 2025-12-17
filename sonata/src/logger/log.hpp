#pragma once
#include <spdlog/spdlog.h>

#include "core.hpp"

namespace Sonata {

typedef std::shared_ptr<spdlog::logger> LoggerPtr;

class Log {
public:
    static void Init();

    static spdlog::logger* GetEngineLogger() { return s_EngineLogger.get(); }
    static spdlog::logger* GetAppLogger() { return s_AppLogger.get(); }

private:
    static LoggerPtr s_EngineLogger;
    static LoggerPtr s_AppLogger;
};

} // namespace Sonata

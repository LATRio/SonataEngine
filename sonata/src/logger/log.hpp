#pragma once
#include <spdlog/spdlog.h>

#include "core.hpp"

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

}

#pragma once
#include "logger/log.hpp"

#define TEXT(x) #x
#define SN_ASSERT(cond) if(!cond) { SN_ENGINE_FATAL("{} is not true", TEXT(cond)); DebugBreak(); }
#define SN_ASSERT_MSG(cond, msg) if(!cond) { SN_ENGINE_FATAL("{}: {}", TEXT(cond), msg); DebugBreak(); }
#define BIT(x) (1 << (x))

#pragma once
#include "logger/log.hpp"

#define TEXT(x) #x
#ifndef NDEBUG
#define SN_ASSERT(cond) if(!(cond)) { SN_ENGINE_FATAL("{} is not true", TEXT(cond)); DebugBreak(); }
#define SN_ASSERT_MSG(cond, msg) if(!(cond)) { SN_ENGINE_FATAL("{}: {}", TEXT(cond), msg); DebugBreak(); }
#else
#define SN_ASSERT(cond)
#define SN_ASSERT_MSG(cond, msg)
#endif
#define BIT(x) (1 << (x))
#define SN_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

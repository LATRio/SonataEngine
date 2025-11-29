#pragma once
#include "log.hpp"

#define TEXT(x) #x
#define SN_ASSERT(cond) if(!(cond)) { SN_ENGINE_FATAL("{} is not true", TEXT(cond)); exit(EXIT_FAILURE); }
#define SN_ASSERT_MSG(cond, msg) if(!(cond)) { SN_ENGINE_FATAL("{}: {}", TEXT(cond), msg); exit(EXIT_FAILURE); }
#define BIT(x) (1 << (x))

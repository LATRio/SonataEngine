#pragma once
#include <csignal>
#include "logger/log.hpp"

#define TEXT(x) #x
#define BIT(x) (1 << (x))
#define SN_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

#ifdef __linux__
#define DebugBreak() raise(SIGTRAP)
#elif _WIN32
#define DebugBreak() __debugbreak()
#else
#define DebugBreak()
#endif

namespace Sonata {

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... p_Args)
{
    return std::make_unique<T>(std::forward<Args>(p_Args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... p_Args)
{
    return std::make_shared<T>(std::forward<Args>(p_Args)...);
}

}

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

#ifndef NDEBUG
#define SN_ENGINE_DEBUG(...) Sonata::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define SN_APP_DEBUG(...) Sonata::Log::GetAppLogger()->debug(__VA_ARGS__)
#else
#define SN_ENGINE_DEBUG(...)
#define SN_APP_DEBUG(...)
#endif

#ifndef NDEBUG
#define SN_ASSERT(cond) if(!(cond)) { SN_ENGINE_FATAL("{} is not true", TEXT(cond)); DebugBreak(); }
#define SN_ASSERT_MSG(cond, msg) if(!(cond)) { SN_ENGINE_FATAL("{}: {}", TEXT(cond), msg); DebugBreak(); }
#else
#define SN_ASSERT(cond)
#define SN_ASSERT_MSG(cond, msg)
#endif

#pragma once
#include <chrono>
#include <fstream>
#include <source_location>
#include <string>
#include <thread>

namespace Sonata {

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult
{
    std::string Name{};
    FloatingPointMicroseconds Start;
    std::chrono::microseconds Duration;
    std::thread::id ThreadID{};
};

struct InstrumentationSession
{
    std::string Name{};
};

class Instrumentor {
public:
    void BeginSession(const std::string& p_Name, const std::string& p_Filepath = "results.json");
    void EndSession();

    void WriteProfile(const ProfileResult& p_Result);
    void WriteHeader();
    void WriteFooter();

    static Instrumentor& GetInstance();

private:
    InstrumentationSession* m_CurrentSession{};
    std::ofstream m_OutputStream;
};

class InstrumentationTimer {
public:
    InstrumentationTimer() = delete;
    explicit InstrumentationTimer(const std::string_view& p_Name)
        : m_Name(p_Name)
        , m_StartTimepoint(std::chrono::steady_clock::now())
    {}
    ~InstrumentationTimer()
    {
        if (!m_Stopped)
        {
            Stop();
        }
    }

    void Stop()
    {
        const auto endTimepoint = std::chrono::steady_clock::now();
        const auto highResStart = FloatingPointMicroseconds{m_StartTimepoint.time_since_epoch()};
        const auto dur{
            std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() -
            std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch()};

        Instrumentor::GetInstance().WriteProfile({m_Name, highResStart, dur, std::this_thread::get_id()});

        m_Stopped = true;
    }

private:
    std::string m_Name;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint{};
    bool m_Stopped{};
};

} // namespace Sonata

/* clang-format off */
#define SN_PROFILE_BEGIN_SESSION(name, filepath) ::Sonata::Instrumentor::GetInstance().BeginSession(name, filepath)
#define SN_PROFILE_END_SESSION() ::Sonata::Instrumentor::GetInstance().EndSession()
#define SN_PROFILE_SCOPE(name) ::Sonata::InstrumentationTimer timer##__LINE__{(name)}
#define SN_PROFILE_FUNCTION() SN_PROFILE_SCOPE(std::source_location::current().function_name())
/* clang-format on */

#include "instrumentor.hpp"

namespace Sonata {

void Instrumentor::BeginSession(const std::string& p_Name, const std::string& p_Filepath)
{
    m_OutputStream.open(p_Filepath.c_str());
    WriteHeader();
    m_CurrentSession = new InstrumentationSession(p_Name);
}

void Instrumentor::EndSession()
{
    WriteFooter();
    m_OutputStream.close();
    delete m_CurrentSession;
    m_CurrentSession = nullptr;
}

void Instrumentor::WriteProfile(const ProfileResult& p_Result)
{
    std::stringstream json;

    json << std::setprecision(3) << std::fixed;
    json << ",{";
    json << R"("cat":"function",)";
    json << R"("dur":)" << p_Result.Duration.count() << ',';
    json << R"("name":")" << p_Result.Name << "\",";
    json << R"("ph":"X",)";
    json << R"("pid":0,)";
    json << R"("tid":)" << p_Result.ThreadID << ',';
    json << R"("ts":)" << p_Result.Start.count();
    json << "}";

    m_OutputStream << json.str();
    m_OutputStream.flush();
}

void Instrumentor::WriteHeader()
{
    m_OutputStream << R"({"otherData":{},"traceEvents":[{})";
    m_OutputStream.flush();
}

void Instrumentor::WriteFooter()
{
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

Instrumentor& Instrumentor::GetInstance()
{
    static Instrumentor s_Instance;
    return s_Instance;
}

}

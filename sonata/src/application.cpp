#include "application.hpp"

#include "log.hpp"
#include "window.hpp"

namespace Sonata {

#define BIND_EVENT_FUNC(func) std::bind(&Application::func, this, std::placeholders::_1)

Application::Application()
{
}

Application::~Application()
{
}

void Application::InitWindow(const int p_Width, const int p_Height, const std::string_view p_Title)
{
    m_Window = std::make_unique<Window>(WindowProps(p_Width, p_Height, p_Title));
    m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
}

void Application::Loop() const
{
    // ReSharper disable once CppDFAConstantConditions
    while (m_IsRunning)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->Update();
    }
}
void Application::OnEvent(const Event &p_Event)
{
    SN_ENGINE_INFO("{}", p_Event.GetName());
    if (p_Event.GetEventType() == EventType::WindowClose)
    {
        m_IsRunning = false;
        m_Window->SetWindowShouldClose(true);
    }
}

} // Sonata
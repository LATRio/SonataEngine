#include "application.hpp"

#include "events/app_event.hpp"
#include "logger/log.hpp"
#include "window.hpp"

namespace Sonata {

#define BIND_EVENT_FUNC(func) std::bind(&Application::func, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application()
{
    SN_ASSERT_MSG(!s_Instance, "Only one instance of Application is allowed!");
    s_Instance = this;
}

Application::~Application()
{
}

void Application::Init(const int p_Width, const int p_Height, const std::string_view p_Title)
{
    m_Window = std::make_unique<Window>(WindowProps(p_Width, p_Height, p_Title));
    m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
}

void Application::Loop()
{
    // ReSharper disable once CppDFAConstantConditions
    while (m_IsRunning)
    {
        m_Window->PollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_LayerStack.OnUpdate();

        m_Window->SwapBuffers();
    }
}

void Application::OnEvent(Event& p_Event)
{
    SN_ENGINE_INFO("{}", p_Event.ToString().c_str());
    EventDispatcher dispatcher(p_Event);
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FUNC(OnWindowClosed));

    m_LayerStack.OnEvent(p_Event);
}

bool Application::OnWindowClosed(const EventWindowClose& p_Event)
{
    m_IsRunning = false;
    return true;
}

void Application::PushLayer(Layer* p_Layer)
{
    m_LayerStack.PushLayer(p_Layer);
}

void Application::PushOverlay(Layer* p_Layer)
{
    m_LayerStack.PushOverlay(p_Layer);
}

void Application::Shutdown()
{
    m_IsRunning = false;
}

} // Sonata
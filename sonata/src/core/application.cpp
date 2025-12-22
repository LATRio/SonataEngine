#include "application.hpp"

#include "events/app_event.hpp"
#include "profiler/instrumentor.hpp"
#include "rendering/renderer.hpp"
#include "window.hpp"

namespace Sonata {

Application* Application::s_Instance = nullptr;

Application::Application()
{
    SN_ASSERT_MSG(!s_Instance, "Only one instance of Application is allowed!");
    s_Instance = this;
}

void Application::Init(const WindowProps& p_Props)
{
    SN_PROFILE_FUNCTION();

    m_Window = CreateScope<Window>(p_Props);
    m_Window->SetEventCallback(SN_BIND_EVENT_FUNC(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

void Application::Loop()
{
    SN_PROFILE_FUNCTION();

    while (m_IsRunning)
    {
        SN_PROFILE_SCOPE("Application Loop");
        const float time = static_cast<float>(glfwGetTime());
        const float deltaTime{time - m_LastFrameTime};
        m_LastFrameTime = time;

        m_Window->PollEvents();

        if (!m_IsMinimized)
        {
            m_LayerStack.OnUpdate(deltaTime);

            m_ImGuiLayer->Begin();
            m_LayerStack.OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->SwapBuffers();
        }
    }
}

void Application::OnEvent(Event& p_Event)
{
    SN_PROFILE_FUNCTION();

    EventDispatcher dispatcher(p_Event);
    dispatcher.Dispatch<EventWindowClose>(SN_BIND_EVENT_FUNC(Application::OnWindowClosed));
    dispatcher.Dispatch<EventFramebufferResize>(SN_BIND_EVENT_FUNC(Application::OnFramebufferResize));

    m_LayerStack.OnEvent(p_Event);
}

bool Application::OnWindowClosed([[maybe_unused]] const EventWindowClose& p_Event)
{
    SN_PROFILE_FUNCTION();

    Shutdown();
    return true;
}

bool Application::OnWindowMinimized(const EventWindowMinimize& p_Event)
{
    SN_PROFILE_FUNCTION();

    m_IsMinimized = p_Event.IsMinimized();
    return true;
}

bool Application::OnFramebufferResize(const EventFramebufferResize& p_Event) const
{
    SN_PROFILE_FUNCTION();

    Renderer::OnFramebufferResize(p_Event.GetWidth(), p_Event.GetHeight());
    return true;
}

void Application::PushLayer(Layer* p_Layer)
{
    SN_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(p_Layer);
}

void Application::PushOverlay(Layer* p_Layer)
{
    SN_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(p_Layer);
}

void Application::Shutdown()
{
    SN_PROFILE_FUNCTION();

    m_IsRunning = false;
}

} // namespace Sonata

#include "application.hpp"

#include "events/app_event.hpp"
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
    m_Window = std::make_unique<Window>(p_Props);
    m_Window->SetEventCallback(SN_BIND_EVENT_FUNC(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

void Application::Loop()
{
    // ReSharper disable once CppDFAConstantConditions
    while (m_IsRunning)
    {
        const float time = static_cast<float>(glfwGetTime());
        const float deltaTime{time - m_LastFrameTime};
        m_LastFrameTime = time;

        m_Window->PollEvents();

        m_LayerStack.OnUpdate(deltaTime);

        m_ImGuiLayer->Begin();
        m_LayerStack.OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->SwapBuffers();
    }
}

void Application::OnEvent(Event& p_Event)
{
    EventDispatcher dispatcher(p_Event);
    dispatcher.Dispatch<EventWindowClose>(SN_BIND_EVENT_FUNC(Application::OnWindowClosed));

    m_LayerStack.OnEvent(p_Event);
}

bool Application::OnWindowClosed(const EventWindowClose& p_Event)
{
    Shutdown();
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
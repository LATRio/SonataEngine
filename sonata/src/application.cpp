#include "application.hpp"

#include "events/app_event.hpp"
#include "logger/log.hpp"
#include "window.hpp"
#include "rendering/opengl/opengl_shader.hpp"

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

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    constexpr unsigned int indices[] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::string_view vertSrc = R"(
        #version 460

        layout(location = 0) in vec3 a_Position;
        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";
    std::string_view fragSrc = R"(
        #version 460

        out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position, 1.0);
        }
    )";

    m_Shader = std::make_unique<OpenGLShader>(vertSrc, fragSrc);
}

void Application::Loop()
{
    // ReSharper disable once CppDFAConstantConditions
    while (m_IsRunning)
    {
        m_Window->PollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        m_Shader->Unbind();

        m_LayerStack.OnUpdate();

        m_ImGuiLayer->Begin();
        m_LayerStack.OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->SwapBuffers();
    }
}

void Application::OnEvent(Event& p_Event)
{
    EventDispatcher dispatcher(p_Event);
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FUNC(OnWindowClosed));

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
#include "application.hpp"

#include "window.hpp"
#include "logger/log.hpp"
#include "events/app_event.hpp"
#include "rendering/vertex_array.hpp"
#include "rendering/buffer.hpp"
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

    m_VertexArray.reset(VertexArray::Create());

    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
         0.0f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
    };
    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VertexBuffer->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
    });
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    constexpr unsigned int indices[] = { 0, 1, 2 };
    m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string_view vertSrc = R"(
        #version 460

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;
        out vec3 v_Position;
        out vec4 v_Color;

        void main()
        {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";
    std::string_view fragSrc = R"(
        #version 460

        out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main()
        {
            color = v_Color;
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
        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        m_VertexArray->Unbind();
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
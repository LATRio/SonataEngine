#include "sandbox.hpp"

#include <sonata.hpp>

class ExampleLayer final : public Sonata::Layer
{
public:
    ExampleLayer()
        : Layer("ExampleLayer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        m_VertexArray.reset(Sonata::VertexArray::Create());

        constexpr float vertices[] = {
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
        };
        std::shared_ptr<Sonata::VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(Sonata::VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->SetLayout({
            {Sonata::ShaderDataType::Float3, "a_Position"},
            {Sonata::ShaderDataType::Float4, "a_Color"},
        });
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        constexpr unsigned int indices[] = { 0, 1, 2 };
        std::shared_ptr<Sonata::IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(Sonata::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_SquareVA.reset(Sonata::VertexArray::Create());
        constexpr float squareVertices[] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
        };
        std::shared_ptr<Sonata::VertexBuffer> m_SquareVB;
        m_SquareVB.reset(Sonata::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        m_SquareVB->SetLayout({
            {Sonata::ShaderDataType::Float3, "a_Position"},
        });
        m_SquareVA->AddVertexBuffer(m_SquareVB);

        constexpr unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Sonata::IndexBuffer> m_SquareIB;
        m_SquareIB.reset(Sonata::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
        m_SquareVA->SetIndexBuffer(m_SquareIB);

        constexpr std::string_view vertSrc = R"(
            #version 460

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProj;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProj * vec4(a_Position, 1.0);
            }
        )";
        constexpr std::string_view fragSrc = R"(
            #version 460

            out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader.reset(Sonata::Shader::Create(vertSrc.data(), fragSrc.data()));

        constexpr std::string_view vertSrc2 = R"(
            #version 460

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProj;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProj * vec4(a_Position, 1.0);
            }
        )";
        constexpr std::string_view fragSrc2 = R"(
            #version 460

            out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";
        m_SquareShader.reset(Sonata::Shader::Create(vertSrc2.data(), fragSrc2.data()));
    }
    ~ExampleLayer() override = default;

    void OnImGuiRender() override
    {
    }

    void OnUpdate(const float p_DeltaTime) override
    {
        SN_APP_TRACE("Delta Time: {}s ({}ms)", p_DeltaTime, p_DeltaTime * 1000.0f);

        m_Velocity = {};
        if (Sonata::Input::IsKeyPressed(SN_KEY_LEFT))
        {
            m_Velocity.x -= m_CameraSpeed * p_DeltaTime;
        }
        if (Sonata::Input::IsKeyPressed(SN_KEY_RIGHT))
        {
            m_Velocity.x += m_CameraSpeed * p_DeltaTime;
        }
        if (Sonata::Input::IsKeyPressed(SN_KEY_DOWN))
        {
            m_Velocity.y -= m_CameraSpeed * p_DeltaTime;
        }
        if (Sonata::Input::IsKeyPressed(SN_KEY_UP))
        {
            m_Velocity.y += m_CameraSpeed * p_DeltaTime;
        }
        m_Camera.Translate(m_Velocity);

        Sonata::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Sonata::RenderCommand::Clear();

        Sonata::Renderer::BeginScene(m_Camera);

        Sonata::Renderer::Submit(m_SquareShader, m_SquareVA);
        Sonata::Renderer::Submit(m_Shader, m_VertexArray);

        Sonata::Renderer::EndScene();
    }

    void OnEvent(Sonata::Event& p_Event) override
    {
        Sonata::EventDispatcher dispatcher(p_Event);
        dispatcher.Dispatch<Sonata::EventKeyPressed>(SN_BIND_EVENT_FUNC(ExampleLayer::OnEventKeyPressed));
    }

    bool OnEventKeyPressed(const Sonata::EventKeyPressed& p_Event)
    {
        return false;
    }

private:
    float m_CameraSpeed = 1.0f;
    glm::vec3 m_Velocity{};

    Sonata::OrthographicCamera m_Camera;

    std::shared_ptr<Sonata::Shader> m_Shader;
    std::shared_ptr<Sonata::VertexArray> m_VertexArray;

    std::shared_ptr<Sonata::Shader> m_SquareShader;
    std::shared_ptr<Sonata::VertexArray> m_SquareVA;
};

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}

void Sandbox::Init(const Sonata::WindowProps& p_Props)
{
    Application::Init(p_Props);

    PushLayer(new ExampleLayer());
}
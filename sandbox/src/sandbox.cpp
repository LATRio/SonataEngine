#include "sandbox.hpp"

#include "glad/gl.h"

#include <sonata.hpp>

class ExampleLayer final : public Sonata::Layer
{
public:
    ExampleLayer()
        : Layer("ExampleLayer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        m_VertexArray.reset(Sonata::VertexArray::Create());
        m_VertexArray->Bind();
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

        constexpr std::string_view vertSrc = R"(
            #version 460

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProj;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        constexpr std::string_view fragSrc = R"(
            #version 460

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader.reset(Sonata::Shader::Create(vertSrc.data(), fragSrc.data()));

        m_SquareVA.reset(Sonata::VertexArray::Create());
        m_SquareVA->Bind();
        constexpr float squareVertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
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

        constexpr std::string_view flatColorShaderVertSrc = R"(
            #version 460

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProj;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        constexpr std::string_view flatColorShaderFragSrc = R"(
            #version 460

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec4 u_Color;

            void main()
            {
                color = u_Color;
            }
        )";
        m_FlatColorShader.reset(Sonata::Shader::Create(flatColorShaderVertSrc.data(), flatColorShaderFragSrc.data()));
    }
    ~ExampleLayer() override = default;

    void OnUpdate(const float p_DeltaTime) override
    {
        //SN_APP_TRACE("Delta Time: {}s ({}ms)", p_DeltaTime, p_DeltaTime * 1000.0f);

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

        const glm::mat4 scale{glm::scale(glm::mat4(1.0f), glm::vec3(0.1f))};

        m_FlatColorShader->Bind();
        m_FlatColorShader->SetVec4("u_Color", m_SquareColor);
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos{static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f};
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Sonata::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        Sonata::Renderer::Submit(m_Shader, m_VertexArray);

        Sonata::Renderer::EndScene();
    }

    void OnEvent(Sonata::Event& p_Event) override
    {
        Sonata::EventDispatcher dispatcher(p_Event);
        dispatcher.Dispatch<Sonata::EventKeyPressed>(SN_BIND_EVENT_FUNC(ExampleLayer::OnEventKeyPressed));
    }

    void OnImGuiRender() override
    {
        using namespace ImGui;

        Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ColorEdit4("Color", glm::value_ptr(m_SquareColor));
        End();
    }

    bool OnEventKeyPressed(const Sonata::EventKeyPressed& p_Event)
    {
        return false;
    }

private:
    float m_CameraSpeed = 2.0f;
    glm::vec3 m_Velocity{};

    Sonata::OrthographicCamera m_Camera;

    std::shared_ptr<Sonata::Shader> m_Shader;
    std::shared_ptr<Sonata::VertexArray> m_VertexArray;

    std::shared_ptr<Sonata::Shader> m_FlatColorShader;
    std::shared_ptr<Sonata::VertexArray> m_SquareVA;

    glm::vec4 m_SquareColor{0.8f, 0.2f, 0.3f, 1.0f};
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
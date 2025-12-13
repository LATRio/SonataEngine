#include "sandbox.hpp"

#include <sonata.hpp>

class ExampleLayer final : public Sonata::Layer
{
public:
    ExampleLayer()
        : Layer("ExampleLayer"), m_CameraController(16.0f / 9.0f)
    {
        m_VertexArray.reset(Sonata::VertexArray::Create());
        m_VertexArray->Bind();
        constexpr float vertices[] = {
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
        };
        Sonata::Ref<Sonata::VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(Sonata::VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->SetLayout({
            {Sonata::ShaderDataType::Float3, "a_Position"},
            {Sonata::ShaderDataType::Float4, "a_Color"},
        });
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        constexpr unsigned int indices[] = { 0, 1, 2 };
        Sonata::Ref<Sonata::IndexBuffer> m_IndexBuffer;
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
        m_Shader = Sonata::Shader::Create("VertexPosColor", vertSrc.data(), fragSrc.data());

        m_SquareVA.reset(Sonata::VertexArray::Create());
        m_SquareVA->Bind();
        constexpr float squareVertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };
        Sonata::Ref<Sonata::VertexBuffer> m_SquareVB;
        m_SquareVB.reset(Sonata::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        m_SquareVB->SetLayout({
            {Sonata::ShaderDataType::Float3, "a_Position"},
            {Sonata::ShaderDataType::Float2, "a_TexCoord"},
        });
        m_SquareVA->AddVertexBuffer(m_SquareVB);

        constexpr unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };
        Sonata::Ref<Sonata::IndexBuffer> m_SquareIB;
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
        m_FlatColorShader = Sonata::Shader::Create("FlatColor", flatColorShaderVertSrc.data(), flatColorShaderFragSrc.data());

        m_Texture = Sonata::Texture2D::Create("assets/container.jpg");
        m_TransparentTexture = Sonata::Texture2D::Create("assets/awesomeface.png");

        m_TextureShader = m_ShaderLibrary.Load("shaders/texture.glsl");
        m_TextureShader->Bind();
        m_TextureShader->SetInt("u_Texture", 0);
    }
    ~ExampleLayer() override = default;

    void OnUpdate(const float p_DeltaTime) override
    {
        m_CameraController.OnUpdate(p_DeltaTime);

        Sonata::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Sonata::RenderCommand::Clear();

        Sonata::Renderer::BeginScene(m_CameraController.GetCamera());

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

        m_Texture->Bind();
        Sonata::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_TransparentTexture->Bind();
        Sonata::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Sonata::Renderer::Submit(m_Shader, m_VertexArray);

        Sonata::Renderer::EndScene();
    }

    void OnEvent(Sonata::Event& p_Event) override
    {
        m_CameraController.OnEvent(p_Event);
    }

    void OnImGuiRender() override
    {
        using namespace ImGui;

        Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ColorEdit4("Color", glm::value_ptr(m_SquareColor));
        End();

        m_CameraController.OnImGuiRender();
    }

private:
    Sonata::ShaderLibrary m_ShaderLibrary;

    Sonata::OrthographicCameraController m_CameraController;

    Sonata::Ref<Sonata::Shader> m_Shader;
    Sonata::Ref<Sonata::VertexArray> m_VertexArray;

    Sonata::Ref<Sonata::Shader> m_FlatColorShader, m_TextureShader;
    Sonata::Ref<Sonata::VertexArray> m_SquareVA;

    Sonata::Ref<Sonata::Texture> m_Texture;
    Sonata::Ref<Sonata::Texture> m_TransparentTexture;

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
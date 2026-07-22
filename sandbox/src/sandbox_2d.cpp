#include "sandbox_2d.hpp"
#include "profiler/instrumentor.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(16.0f / 9.0f)
{}

void Sandbox2D::OnAttach()
{
    SN_PROFILE_FUNCTION();

    Sonata::Renderer2D::Init();
    m_Texture = Sonata::Texture2D::Create("assets/container.jpg");
    m_Spritesheet = Sonata::Texture2D::Create("assets/RPGpack_sheet_2X.png");

    m_TextureStairs = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {7, 6}, {128, 128}, {1, 1});
    m_TextureBarrel = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {8, 2}, {128, 128}, {1, 1});
    m_TextureTree = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {2, 1}, {128, 128}, {1, 2});
}

void Sandbox2D::OnDetach()
{
    SN_PROFILE_FUNCTION();

    Sonata::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(const float p_DeltaTime)
{
    SN_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(p_DeltaTime);

    Sonata::Renderer2D::ResetStats();

    Sonata::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Sonata::RenderCommand::Clear();

    static float rotation{0.0f};
    rotation += 50.0f * p_DeltaTime;

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Sonata::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, 45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
    Sonata::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Sonata::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
    Sonata::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_Texture, 20.0f);
    Sonata::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, m_Texture, 20.0f);
    Sonata::Renderer2D::EndScene();

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y < 5.0f; y += 0.5f)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            glm::vec4 color{(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
            Sonata::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
        }
    }
    Sonata::Renderer2D::EndScene();

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Sonata::Renderer2D::DrawQuad({0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, m_TextureStairs);
    Sonata::Renderer2D::DrawQuad({1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, m_TextureBarrel);
    Sonata::Renderer2D::DrawQuad({-1.0f, 0.5f, 1.0f}, {1.0f, 2.0f}, m_TextureTree);
    Sonata::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Sonata::Event& p_Event)
{
    SN_PROFILE_FUNCTION();

    m_CameraController.OnEvent(p_Event);
}

void Sandbox2D::OnImGuiRender()
{
    SN_PROFILE_FUNCTION();

    using namespace ImGui;

    const auto stats = Sonata::Renderer2D::GetStats();

    Begin("Settings", nullptr, ImGuiChildFlags_AlwaysAutoResize);

    Text("Renderer2D Stats:");
    Text("Draw Calls: %d", stats.DrawCalls);
    Text("Quads: %d", stats.QuadCount);
    Text("Vertices: %d", stats.GetTotalVertexCount());
    Text("Indices: %d", stats.GetTotalIndexCount());

    End();
}

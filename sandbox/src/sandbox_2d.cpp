#include "sandbox_2d.hpp"
#include "profiler/instrumentor.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
    SN_PROFILE_FUNCTION();

    Sonata::Renderer2D::Init();
    m_Texture = Sonata::Texture2D::Create("assets/awesomeface.png");
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

    Sonata::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Sonata::RenderCommand::Clear();

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Sonata::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Sonata::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
    Sonata::Renderer2D::DrawQuad({0.2f, 0.5f}, {0.5f, 0.5f}, m_Texture);

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

    m_CameraController.OnImGuiRender();
}

#pragma once
#include <sonata.hpp>

class Sandbox2D final : public Sonata::Layer {
public:
    explicit Sandbox2D();
    ~Sandbox2D() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float p_DeltaTime) override;
    void OnEvent(Sonata::Event& p_Event) override;
    void OnImGuiRender() override;

private:
    Sonata::OrthographicCameraController m_CameraController;

    Sonata::Ref<Sonata::VertexArray> m_SquareVA;
    Sonata::Ref<Sonata::Shader> m_FlatColorShader;

    Sonata::Ref<Sonata::Texture2D> m_Texture;

    glm::vec4 m_SquareColor{0.8f, 0.2f, 0.3f, 1.0f};
};

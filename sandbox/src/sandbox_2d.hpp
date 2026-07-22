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
    Sonata::Ref<Sonata::Texture2D> m_Spritesheet;
    Sonata::Ref<Sonata::SubTexture2D> m_TextureStairs;
    Sonata::Ref<Sonata::SubTexture2D> m_TextureBarrel;
    Sonata::Ref<Sonata::SubTexture2D> m_TextureTree;

    std::unordered_map<char, Sonata::Ref<Sonata::SubTexture2D>> m_TextureMap;

    glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };

    uint32_t m_MapWidth{};
    uint32_t m_MapHeight{};
};

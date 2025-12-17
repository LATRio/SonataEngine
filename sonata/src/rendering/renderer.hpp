#pragma once
#include "glm_wrapper.hpp"
#include "render_command.hpp"

namespace Sonata {

class Shader;
class OrthographicCamera;
class VertexArray;

class Renderer {
public:
    static void Init();

    static void BeginScene(const OrthographicCamera& p_Camera);
    static void EndScene() {}

    static void Submit(
        const Ref<Shader>& p_Shader, const Ref<VertexArray>& p_VertexArray,
        const glm::mat4& p_Transform = glm::mat4{1.0f});

    static void OnFramebufferResize(int p_Width, int p_Height);

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjMatrix;
    };

    static SceneData* s_SceneData;
};

} // namespace Sonata

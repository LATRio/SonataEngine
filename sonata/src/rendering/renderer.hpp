#pragma once
#include "render_command.hpp"
#include "glm_wrapper.hpp"

namespace Sonata {

class Shader;
class OrthographicCamera;
class VertexArray;

class Renderer {
public:
    static void BeginScene(const OrthographicCamera& p_Camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray, const glm::mat4& p_Transform = glm::mat4{1.0f});

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjMatrix;
    };

    static SceneData* s_SceneData;
};

}

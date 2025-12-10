#include "renderer.hpp"
#include "orthographic_camera.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"

namespace Sonata {

Renderer::SceneData* Renderer::s_SceneData = new SceneData();

void Renderer::BeginScene(const OrthographicCamera& p_Camera)
{
    s_SceneData->ViewProjMatrix = p_Camera.GetViewProjMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const Ref<Shader>& p_Shader, const Ref<VertexArray>& p_VertexArray, const glm::mat4& p_Transform)
{
    p_Shader->Bind();
    p_Shader->SetMat4("u_ViewProj", s_SceneData->ViewProjMatrix);
    p_Shader->SetMat4("u_Transform", p_Transform);

    p_VertexArray->Bind();
    RenderCommand::DrawIndexed(p_VertexArray);
}

}
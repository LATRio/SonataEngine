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

void Renderer::Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray)
{
    p_Shader->Bind();
    p_Shader->SetMat4("u_ViewProj", s_SceneData->ViewProjMatrix);

    p_VertexArray->Bind();
    RenderCommand::DrawIndexed(p_VertexArray);
}

}
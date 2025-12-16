#include "renderer_2d.hpp"

#include "buffer.hpp"
#include "render_command.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

namespace Sonata {

struct Renderer2DStorage
{
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> FlatColorShader;
    Ref<Shader> TextureShader;
};

static Renderer2DStorage* s_Data;

void Renderer2D::Init()
{
    s_Data = new Renderer2DStorage();
    s_Data->QuadVertexArray = VertexArray::Create();
    constexpr float squareVertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    const Ref<VertexBuffer> m_SquareVB =
        VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    m_SquareVB->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"},
    });
    s_Data->QuadVertexArray->AddVertexBuffer(m_SquareVB);

    constexpr unsigned int squareIndices[] = {0, 1, 2, 2, 3, 0};
    const Ref<IndexBuffer> m_SquareIB =
        IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
    s_Data->QuadVertexArray->SetIndexBuffer(m_SquareIB);

    s_Data->FlatColorShader = Shader::Create("shaders/flatcolor.glsl");
    s_Data->TextureShader = Shader::Create("shaders/texture.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);
}

void Renderer2D::Shutdown()
{
    delete s_Data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());

    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());
}

void Renderer2D::EndScene()
{
}

void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
{
    DrawQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Color);
}

void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
{
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetVec4("u_Color", p_Color);

    const glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));
    s_Data->FlatColorShader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture)
{
    DrawQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Texture);
}

void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture)
{
    s_Data->TextureShader->Bind();

    const glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));
    s_Data->TextureShader->SetMat4("u_Transform", transform);

    p_Texture->Bind();

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

}

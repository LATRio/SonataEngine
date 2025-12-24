#include "renderer_2d.hpp"
#include <array>

#include "buffer.hpp"
#include "profiler/instrumentor.hpp"
#include "render_command.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

namespace Sonata {

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    int32_t TexIndex;
    float TilingFactor;
};

struct Renderer2DData
{
    static constexpr int64_t MaxQuads{10000};
    static constexpr int64_t MaxVertices{MaxQuads * 4};
    static constexpr int64_t MaxIndices{MaxQuads * 6};
    static constexpr int64_t MaxTextureSlots{32};

    Ref<VertexArray> QuadVertexArray;
    Ref<VertexBuffer> QuadVertexBuffer;
    Ref<Shader> TextureShader;
    Ref<Texture2D> WhiteTexture;

    int32_t QuadIndexCount{};
    QuadVertex* QuadVertexBufferBase{};
    QuadVertex* QuadVertexBufferPtr{};

    std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots{};
    uint32_t TextureSlotIndex{1};

    glm::vec4 QuadVertexPositions[4];
};

static Renderer2DData s_Data;
glm::vec4 Renderer2D::s_TintColor = glm::vec4(1.0f);

void Renderer2D::Init()
{
    SN_PROFILE_FUNCTION();

    s_Data.QuadVertexArray = VertexArray::Create();
    s_Data.QuadVertexBuffer =
        VertexBuffer::Create(Renderer2DData::MaxVertices * static_cast<int64_t>(sizeof(QuadVertex)));
    s_Data.QuadVertexBuffer->SetLayout({
        {ShaderDataType::Float3,     "a_Position"},
        {ShaderDataType::Float4,        "a_Color"},
        {ShaderDataType::Float2,     "a_TexCoord"},
        {   ShaderDataType::Int,     "a_TexIndex"},
        { ShaderDataType::Float, "a_TilingFactor"},
    });
    s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVertices]{};

    uint32_t* quadIndices = new uint32_t[Renderer2DData::MaxIndices];

    uint32_t offset{};
    for (uint32_t i = 0; i < Renderer2DData::MaxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, Renderer2DData::MaxIndices);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    constexpr uint32_t whiteTextureData{0xffffffff};
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int32_t samplers[Renderer2DData::MaxTextureSlots];
    for (int32_t i = 0; i < Renderer2DData::MaxTextureSlots; i++)
    {
        samplers[i] = i;
    }

    s_Data.TextureShader = Shader::Create("shaders/texture.glsl");
    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetIntN("u_Texture", samplers, Renderer2DData::MaxTextureSlots);

    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::Shutdown()
{
    SN_PROFILE_FUNCTION();
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    SN_PROFILE_FUNCTION();

    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());

    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.QuadIndexCount = 0;

    // s_Data.TextureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
    SN_PROFILE_FUNCTION();

    const int64_t dataSize{
        reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferPtr) -
        reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferBase)};
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    Flush();
}

void Renderer2D::Flush()
{
    SN_PROFILE_FUNCTION();

    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
    {
        s_Data.TextureSlots[i]->Bind(i);
    }
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
{
    DrawQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Color);
}

void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
{
    SN_PROFILE_FUNCTION();

    constexpr int32_t texIndex{};
    constexpr float tilingFactor{1.0f};

    const glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawQuad(
    const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, const float p_TilingFactor)
{
    DrawQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Texture, p_TilingFactor);
}

void Renderer2D::DrawQuad(
    const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, const float p_TilingFactor)
{
    SN_PROFILE_FUNCTION();

    int32_t textureIndex{};
    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if (*s_Data.TextureSlots[i].get() == *p_Texture.get())
        {
            textureIndex = static_cast<int32_t>(i);
            break;
        }
    }

    if (textureIndex == 0)
    {
        textureIndex = static_cast<int32_t>(s_Data.TextureSlotIndex);
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = p_Texture;
        s_Data.TextureSlotIndex++;
    }

    constexpr glm::vec4 color{1.0f};

    const glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawRotatedQuad(
    const glm::vec2& p_Position, const glm::vec2& p_Size, const float p_Rotation, const glm::vec4& p_Color)
{
    DrawRotatedQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Rotation, p_Color);
}

void Renderer2D::DrawRotatedQuad(
    const glm::vec3& p_Position, const glm::vec2& p_Size, const float p_Rotation, const glm::vec4& p_Color)
{
    SN_PROFILE_FUNCTION();

    constexpr int32_t texIndex{};
    constexpr float tilingFactor{1.0f};

    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(p_Rotation), {0.0f, 0.0f, 1.0f}) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = p_Color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawRotatedQuad(
    const glm::vec2& p_Position, const glm::vec2& p_Size, const float p_Rotation, const Ref<Texture2D>& p_Texture,
    const float p_TilingFactor)
{
    DrawRotatedQuad({p_Position.x, p_Position.y, 0.0f}, p_Size, p_Rotation, p_Texture, p_TilingFactor);
}

void Renderer2D::DrawRotatedQuad(
    const glm::vec3& p_Position, const glm::vec2& p_Size, [[maybe_unused]] const float p_Rotation,
    const Ref<Texture2D>& p_Texture, const float p_TilingFactor)
{
    SN_PROFILE_FUNCTION();

    int32_t textureIndex{};
    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if (*s_Data.TextureSlots[i].get() == *p_Texture.get())
        {
            textureIndex = static_cast<int32_t>(i);
            break;
        }
    }

    if (textureIndex == 0)
    {
        textureIndex = static_cast<int32_t>(s_Data.TextureSlotIndex);
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = p_Texture;
        s_Data.TextureSlotIndex++;
    }

    constexpr glm::vec4 color{1.0f};

    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(p_Rotation), {0.0f, 0.0f, 1.0f}) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(p_Size.x, p_Size.y, 1.0f));

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color = color;
    s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
    s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;
}

} // namespace Sonata

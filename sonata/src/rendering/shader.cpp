#include "shader.hpp"

#include "opengl/opengl_shader.hpp"
#include "renderer.hpp"

namespace Sonata {

Ref<Shader> Shader::Create(const std::string_view p_Filepath)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(p_Filepath);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

Ref<Shader> Shader::Create(
    const std::string_view p_Name, const std::string_view p_VertexPath, const std::string_view p_FragmentPath)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(p_Name, p_VertexPath, p_FragmentPath);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

void ShaderLibrary::Add(const Ref<Shader>& p_Shader)
{
    const auto name{p_Shader->GetName()};
    Add(name, p_Shader);
}

void ShaderLibrary::Add(const std::string_view p_Name, const Ref<Shader>& p_Shader)
{
    SN_ASSERT_MSG(!Exists(p_Name), std::format("Shader '{}' already exists!", p_Name));
    m_Shaders[p_Name.data()] = p_Shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string_view p_Filepath)
{
    auto shader{Shader::Create(p_Filepath)};
    Add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string_view p_Name, const std::string_view p_Filepath)
{
    auto shader{Shader::Create(p_Filepath)};
    Add(p_Name, shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string_view p_Name)
{
    SN_ASSERT_MSG(Exists(p_Name), std::format("Shader '{}' not found!", p_Name));
    return m_Shaders[p_Name.data()];
}

bool ShaderLibrary::Exists(const std::string_view p_Name) const
{
    return m_Shaders.contains(p_Name.data());
}

} // namespace Sonata

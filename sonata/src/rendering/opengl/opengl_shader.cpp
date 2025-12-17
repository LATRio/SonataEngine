#include "opengl_shader.hpp"

#include <fstream>
#include <filesystem>

#include "core.hpp"
#include "glm_wrapper.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata {

GLenum StrToType(std::string_view p_Type)
{
    if (p_Type == "vertex") return GL_VERTEX_SHADER;
    if (p_Type == "fragment" || p_Type == "pixel") return GL_FRAGMENT_SHADER;
    if (p_Type == "geometry") return GL_GEOMETRY_SHADER;

    SN_ENGINE_ERR("Unknown shader type '{}'", p_Type);
    return 0;
}

OpenGLShader::OpenGLShader(const std::string_view p_Filepath)
{
    SN_PROFILE_FUNCTION();

    m_Name = std::filesystem::path(p_Filepath).stem().string();
    const std::string source = ReadFile(p_Filepath);
    auto shaderSources = Preprocess(source);
    CompileShaders(shaderSources);
}

OpenGLShader::OpenGLShader(const std::string_view p_Name, const std::string_view p_VertSrc, const std::string_view p_FragSrc)
    : m_Name(p_Name)
{
    SN_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> shaderSources;
    shaderSources.reserve(2);
    shaderSources[GL_VERTEX_SHADER] = p_VertSrc;
    shaderSources[GL_FRAGMENT_SHADER] = p_FragSrc;
    CompileShaders(shaderSources);
}

OpenGLShader::~OpenGLShader()
{
    SN_PROFILE_FUNCTION();

    glDeleteProgram(m_ProgramID);
}

void OpenGLShader::Bind() const
{
    SN_PROFILE_FUNCTION();

    glUseProgram(m_ProgramID);
}

void OpenGLShader::Unbind() const
{
    SN_PROFILE_FUNCTION();

    glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string_view p_Name, const int p_Value)
{
    SN_PROFILE_FUNCTION();

    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.data());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniform1i(location, p_Value);
}

void OpenGLShader::SetVec3(const std::string_view p_Name, const glm::vec3& p_Value)
{
    SN_PROFILE_FUNCTION();

    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.data());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniform3f(location, p_Value.x, p_Value.y, p_Value.z);
}

void OpenGLShader::SetVec4(const std::string_view p_Name, const glm::vec4& p_Value)
{
    SN_PROFILE_FUNCTION();

    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.data());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniform4f(location, p_Value.x, p_Value.y, p_Value.z, p_Value.w);
}

void OpenGLShader::SetMat4(const std::string_view p_Name, const glm::mat4& p_Value)
{
    SN_PROFILE_FUNCTION();

    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.data());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(p_Value));
}

std::string OpenGLShader::ReadFile(std::string_view p_FilePath) const
{
    SN_PROFILE_FUNCTION();

    std::ifstream in{p_FilePath.data()};
    if (in.is_open())
    {
        in.seekg(0, std::ios::end);
        std::string result;
        result.resize(static_cast<size_t>(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&result[0], static_cast<std::streamsize>(result.size()));
        in.close();

        return result;
    }

    SN_ENGINE_ERR("Could not open file \"{}\"", p_FilePath);
    return "";
}

std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(std::string_view p_Source) const
{
    SN_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> shaderSources;

    auto* typeToken{"#type"};
    const size_t typeTokenLength{strlen(typeToken)};

    size_t posToken{p_Source.find(typeToken, 0)};

    while (posToken != std::string::npos)
    {
        const size_t eol = p_Source.find_first_of('\n', posToken);
        SN_ASSERT_MSG(eol != std::string::npos, "Syntax error! Could not find '\\n'");
        const size_t begin{posToken + typeTokenLength + 1};
        std::string type{p_Source.substr(begin, eol - begin)};
        SN_ASSERT_MSG(StrToType(type), std::format("Invalid shader type '{}'", type));

        const size_t nextLinePos{p_Source.find_first_not_of('\n', eol)};
        posToken = p_Source.find(typeToken, nextLinePos);
        shaderSources[StrToType(type)] = p_Source.substr(nextLinePos,
            posToken - (nextLinePos == std::string::npos ? p_Source.size() - 1 : nextLinePos));
    }

    return shaderSources;
}

void OpenGLShader::CompileShaders(const std::unordered_map<GLenum, std::string>& p_ShaderSources)
{
    SN_PROFILE_FUNCTION();

    m_ProgramID = glCreateProgram();
    SN_ASSERT_MSG(p_ShaderSources.size() <= 2, "Too many shaders! Only 2 supported for now.");
    std::array<GLuint, 2> shaderIDs{};
    size_t shaderIDIndex{};
    for (const auto& [type, src] : p_ShaderSources)
    {
        const GLuint shader = glCreateShader(type);

        const GLchar* source = src.c_str();
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLint maxLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(static_cast<size_t>(maxLength));
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);
            SN_ENGINE_FATAL("Shader compilation failed:\n{}", infoLog.data());
        }

        glAttachShader(m_ProgramID, shader);
        shaderIDs[shaderIDIndex++] = shader;
    }
    glLinkProgram(m_ProgramID);

    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(static_cast<size_t>(maxLength));
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

        for (const auto id : shaderIDs)
        {
            glDeleteShader(id);
        }
        glDeleteProgram(m_ProgramID);

        SN_ENGINE_FATAL("Shader linking failed!\n{}", infoLog.data());
    }

    for (const auto id : shaderIDs)
    {
        glDetachShader(m_ProgramID, id);
    }
}

}

#include "opengl_shader.hpp"

#include "core.hpp"
#include "glm_wrapper.hpp"

namespace Sonata {

OpenGLShader::OpenGLShader(const std::string_view& p_VertSrc, const std::string_view& p_FragSrc)
{
    const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, p_VertSrc);
    const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, p_FragSrc);

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(static_cast<size_t>(maxLength));
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(m_ProgramID);

        SN_ENGINE_FATAL("Shader linking failed!\n{}", infoLog.data());
    }

    // glValidateProgram(m_ProgramID);
    // glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &success);
    // if (success == GL_FALSE)
    // {
    //     GLint maxLength;
    //     glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
    //
    //     std::vector<GLchar> infoLog(static_cast<size_t>(maxLength));
    //     glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);
    //
    //     SN_ENGINE_FATAL("Shader validation failed!\n{}", infoLog.data());
    // }

    glDetachShader(m_ProgramID, vertexShader);
    glDetachShader(m_ProgramID, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_ProgramID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_ProgramID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::SetVec4(const std::string& p_Name, const glm::vec4& p_Value)
{
    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.c_str());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniform4fv(location, 1, glm::value_ptr(p_Value));
}

void OpenGLShader::SetMat4(const std::string& p_Name, const glm::mat4& p_Value)
{
    const GLint location = glGetUniformLocation(m_ProgramID, p_Name.c_str());
    SN_ASSERT_MSG(location != -1, std::format("Uniform location wasn't found! Program: {} ({})", m_ProgramID, p_Name));
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(p_Value));
}

GLuint OpenGLShader::CompileShader(const GLenum p_Type, const std::string_view p_Source)
{
    const GLuint shader = glCreateShader(p_Type);

    const GLchar* src = p_Source.data();
    glShaderSource(shader, 1, &src, nullptr);
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
        SN_ENGINE_FATAL("Shader compilation failed!\n{}", infoLog.data());

    }

    return shader;
}

}

#include "opengl_shader.hpp"

#include "core.hpp"

namespace Sonata {

OpenGLShader::OpenGLShader(const std::string_view& p_vertSrc, const std::string_view& p_fragSrc)
{
    const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, p_vertSrc);
    const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, p_fragSrc);
    
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);
    //glValidateProgram(m_ProgramID);

    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(static_cast<size_t>(maxLength));
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(m_ProgramID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        SN_ENGINE_FATAL("Shader linking failed!\n{}", infoLog.data());
    }

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

void OpenGLShader::Unbind()
{
    glUseProgram(0);
}

GLuint OpenGLShader::CompileShader(const GLenum type, const std::string_view source)
{
    const GLuint shader = glCreateShader(type);

    const GLchar* src = source.data();
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

} // namespace Sonata

#pragma once
#include <glad/gl.h>

namespace Sonata {

class OpenGLShader {
public:
    OpenGLShader(const std::string_view& p_vertSrc, const std::string_view& p_fragSrc);
    ~OpenGLShader();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_ProgramID{};

    static GLuint CompileShader(GLenum type, std::string_view source);
};

}

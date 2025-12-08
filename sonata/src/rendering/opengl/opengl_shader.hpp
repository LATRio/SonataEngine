#pragma once
#include <glad/gl.h>

#include "rendering/shader.hpp"

namespace Sonata {

class OpenGLShader final : public Shader {
public:
    OpenGLShader(const std::string_view& p_vertSrc, const std::string_view& p_fragSrc);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    void SetMat4(const std::string& p_Name, const glm::mat4& p_Matrix) override;

private:
    GLuint m_ProgramID{};

    GLuint CompileShader(GLenum type, std::string_view source);
};

}

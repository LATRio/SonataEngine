#pragma once
#include <glad/gl.h>

#include "rendering/shader.hpp"

namespace Sonata {

class OpenGLShader final : public Shader {
public:
    OpenGLShader(const std::string_view& p_VertSrc, const std::string_view& p_FragSrc);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    void SetVec4(const std::string& p_Name, const glm::vec4& p_Value) override;
    void SetMat4(const std::string& p_Name, const glm::mat4& p_Value) override;

private:
    GLuint m_ProgramID{};

    GLuint CompileShader(GLenum p_Type, std::string_view p_Source);
};

}

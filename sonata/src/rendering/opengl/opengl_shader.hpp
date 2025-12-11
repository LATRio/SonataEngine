#pragma once
#include <glad/gl.h>

#include "rendering/shader.hpp"

namespace Sonata {

class OpenGLShader final : public Shader {
public:
    explicit OpenGLShader(std::string_view p_FilePath);
    OpenGLShader(std::string_view p_VertSrc, std::string_view p_FragSrc);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    void SetInt(std::string_view p_Name, int p_Value) override;
    void SetVec3(std::string_view p_Name, const glm::vec3& p_Value) override;
    void SetVec4(std::string_view p_Name, const glm::vec4& p_Value) override;
    void SetMat4(std::string_view p_Name, const glm::mat4& p_Value) override;

private:
    GLuint m_ProgramID{};

    [[nodiscard]] std::string ReadFile(std::string_view p_FilePath) const;
    [[nodiscard]] std::unordered_map<GLenum, std::string> Preprocess(std::string_view p_Source) const;
    void CompileShaders(const std::unordered_map<GLenum, std::string>& p_ShaderSources);
};

}

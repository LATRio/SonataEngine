#pragma once
#include "glm_wrapper.hpp"

namespace Sonata {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetInt(std::string_view p_Name, int p_Value) = 0;
    virtual void SetVec3(std::string_view p_Name, const glm::vec3& p_Value) = 0;
    virtual void SetVec4(std::string_view p_Name, const glm::vec4& p_Value) = 0;
    virtual void SetMat4(std::string_view p_Name, const glm::mat4& p_Value) = 0;

    static Shader* Create(std::string_view p_FilePath);
    static Shader* Create(std::string_view p_VertexPath, std::string_view p_FragmentPath);
};

}

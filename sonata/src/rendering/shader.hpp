#pragma once
#include "glm_wrapper.hpp"

namespace Sonata {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetMat4(const std::string& p_Name, const glm::mat4& p_Matrix) = 0;

    static Shader* Create(const char* vertexPath, const char* fragmentPath);
};

}

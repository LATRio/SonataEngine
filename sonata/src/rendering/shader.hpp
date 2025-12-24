#pragma once
#include "core.hpp"
#include "glm_wrapper.hpp"

namespace Sonata {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetInt(std::string_view p_Name, int p_Value) = 0;
    virtual void SetIntN(std::string_view p_Name, const int* p_Value, int p_Count) = 0;
    virtual void SetFloat(std::string_view p_Name, float p_Value) = 0;
    virtual void SetFloat3(std::string_view p_Name, const glm::vec3& p_Value) = 0;
    virtual void SetFloat4(std::string_view p_Name, const glm::vec4& p_Value) = 0;
    virtual void SetMat4(std::string_view p_Name, const glm::mat4& p_Value) = 0;

    [[nodiscard]] virtual std::string_view GetName() const = 0;

    virtual void PrintAttributesAndUniforms() = 0;

    static Ref<Shader> Create(std::string_view p_Filepath);
    static Ref<Shader> Create(std::string_view p_Name, std::string_view p_VertexPath, std::string_view p_FragmentPath);
};

class ShaderLibrary {
public:
    void Add(const Ref<Shader>& p_Shader);
    void Add(std::string_view p_Name, const Ref<Shader>& p_Shader);
    Ref<Shader> Load(std::string_view p_Filepath);
    Ref<Shader> Load(std::string_view p_Name, std::string_view p_Filepath);

    Ref<Shader> Get(std::string_view p_Name);

    bool Exists(std::string_view p_Name) const;

private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

} // namespace Sonata

#pragma once
#include "glm_wrapper.hpp"

namespace Sonata {

class OrthographicCamera {
public:
    OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top);

    void SetPosition(const glm::vec3& p_Position);
    [[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }

    void SetRotation(float p_Rotation);
    [[nodiscard]] float GetRotation() const { return m_Rotation; }

    void SetProjection(float p_Left, float p_Right, float p_Bottom, float p_Top);

    [[nodiscard]] const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    [[nodiscard]] const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
    [[nodiscard]] const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMatrix; }

private:
    glm::mat4 m_ProjMatrix{};
    glm::mat4 m_ViewMatrix{1.0f};
    glm::mat4 m_ViewProjMatrix{};

    glm::vec3 m_Position{};
    float m_Rotation{};

    void RecalculateViewMatrix();
};

}

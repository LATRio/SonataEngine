#include "orthographic_camera.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Sonata {

OrthographicCamera::OrthographicCamera(const float p_Left, const float p_Right, const float p_Bottom, const float p_Top)
    : m_ProjMatrix(glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f))
{
    SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));
}

void OrthographicCamera::Translate(const glm::vec3& p_Translation)
{
    m_Position += p_Translation;
    RecalculateViewMatrix();
}

void OrthographicCamera::SetPosition(const glm::vec3& p_Position)
{
    m_Position = p_Position;
    RecalculateViewMatrix();
}

void OrthographicCamera::SetRotation(const float p_Rotation)
{
    m_Rotation = p_Rotation;
    RecalculateViewMatrix();
}

void OrthographicCamera::RecalculateViewMatrix()
{
    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
}

}

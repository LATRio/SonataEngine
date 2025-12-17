#include "orthographic_camera.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata {

OrthographicCamera::OrthographicCamera(const float p_Left, const float p_Right, const float p_Bottom, const float p_Top)
    : m_ProjMatrix(glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f))
{
    SN_PROFILE_FUNCTION();

    m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjection(const float p_Left, const float p_Right, const float p_Bottom, const float p_Top)
{
    SN_PROFILE_FUNCTION();

    m_ProjMatrix = glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f);
    m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetPosition(const glm::vec3& p_Position)
{
    SN_PROFILE_FUNCTION();

    m_Position = p_Position;
    RecalculateViewMatrix();
}

void OrthographicCamera::SetRotation(const float p_Rotation)
{
    SN_PROFILE_FUNCTION();

    m_Rotation = p_Rotation;
    RecalculateViewMatrix();
}

void OrthographicCamera::RecalculateViewMatrix()
{
    SN_PROFILE_FUNCTION();

    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
}

} // namespace Sonata

#include "orthographic_camera_controller.hpp"

#include "events/app_event.hpp"
#include "events/mouse_event.hpp"
#include "input.hpp"

namespace Sonata {

OrthographicCameraController::OrthographicCameraController(const float p_AspectRation, const bool p_CanRotate)
    : m_AspectRatio(p_AspectRation), m_CanRotate(p_CanRotate),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
}

void OrthographicCameraController::OnUpdate(const float p_DeltaTime)
{
    if (Input::IsKeyPressed(SN_KEY_LEFT))
    {
        m_Position.x -= m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(SN_KEY_RIGHT))
    {
        m_Position.x += m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(SN_KEY_DOWN))
    {
        m_Position.y -= m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(SN_KEY_UP))
    {
        m_Position.y += m_TranslationSpeed * p_DeltaTime;
    }
    m_Camera.SetPosition(m_Position);

    if (m_CanRotate)
    {
        if (Input::IsKeyPressed(SN_KEY_Q))
        {
            m_Rotation += m_RotationSpeed * p_DeltaTime;
        }
        if (Input::IsKeyPressed(SN_KEY_E))
        {
            m_Rotation -= m_RotationSpeed * p_DeltaTime;
        }

        m_Camera.SetRotation(m_Rotation);
    }
}

void OrthographicCameraController::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<EventMouseScrolled>(SN_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<EventWindowResize>(SN_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
}

void OrthographicCameraController::OnImGuiRender()
{
    using namespace ImGui;

    Begin("Camera Controller", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    DragFloat3("Position", glm::value_ptr(m_Position), 0.01f);
    DragFloat("Movement Speed", &m_TranslationSpeed, 0.01f, 0.0f);
    Checkbox("Can Rotate", &m_CanRotate);
    BeginDisabled(!m_CanRotate);
    DragFloat("Rotation", &m_Rotation);
    EndDisabled();
    DragFloat("Rotation Speed", &m_RotationSpeed);
    DragFloat("ZoomLevel", &m_ZoomLevel, 0.1f, m_ZoomLevelMin);
    DragFloat("Zoom Sensitivity", &m_ZoomSensitivity, 0.01f, 0.0f);
    End();
}

bool OrthographicCameraController::OnMouseScrolled(const EventMouseScrolled& p_Event)
{
    m_ZoomLevel -= p_Event.GetOffsetY() * m_ZoomSensitivity;
    m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomLevelMin);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(const EventWindowResize& p_Event)
{
    m_AspectRatio = p_Event.GetAspectRatio();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}

}

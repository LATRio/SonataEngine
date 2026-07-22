#include "orthographic_camera_controller.hpp"

#include "core/input.hpp"
#include "events/app_event.hpp"
#include "events/mouse_event.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata {

void OrthographicCameraController::OnUpdate(const float p_DeltaTime)
{
    SN_PROFILE_FUNCTION();

    if (Input::IsKeyPressed(Key::LEFT))
    {
        m_Position.x -= m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(Key::RIGHT))
    {
        m_Position.x += m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(Key::DOWN))
    {
        m_Position.y -= m_TranslationSpeed * p_DeltaTime;
    }
    if (Input::IsKeyPressed(Key::UP))
    {
        m_Position.y += m_TranslationSpeed * p_DeltaTime;
    }
    m_Camera.SetPosition(m_Position);

    // ReSharper disable once CppDFAConstantConditions
    if (m_CanRotate)
    {
        // ReSharper disable once CppDFAUnreachableCode
        if (Input::IsKeyPressed(Key::Q))
        {
            m_Rotation += m_RotationSpeed * p_DeltaTime;
        }
        if (Input::IsKeyPressed(Key::E))
        {
            m_Rotation -= m_RotationSpeed * p_DeltaTime;
        }

        m_Camera.SetRotation(m_Rotation);
    }
}

void OrthographicCameraController::OnEvent(Event& e)
{
    SN_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<EventMouseScrolled>(SN_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<EventWindowResize>(SN_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
}

void OrthographicCameraController::CalculateView()
{
    SN_PROFILE_FUNCTION();

    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

bool OrthographicCameraController::OnMouseScrolled(const EventMouseScrolled& p_Event)
{
    SN_PROFILE_FUNCTION();

    m_ZoomLevel -= p_Event.GetOffsetY() * m_ZoomSensitivity;
    m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomLevelMin);
    CalculateView();
    return false;
}

bool OrthographicCameraController::OnWindowResized(const EventWindowResize& p_Event)
{
    SN_PROFILE_FUNCTION();

    m_AspectRatio = p_Event.GetAspectRatio();
    CalculateView();
    return false;
}

} // namespace Sonata

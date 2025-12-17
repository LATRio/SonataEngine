#pragma once
#include "events/event.hpp"
#include "orthographic_camera.hpp"

namespace Sonata {

class EventWindowResize;
class EventMouseScrolled;

class OrthographicCameraController {
public:
    explicit OrthographicCameraController(const float p_AspectRation, const bool p_CanRotate = false)
        : m_AspectRatio(p_AspectRation)
        , m_CanRotate(p_CanRotate)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {}

    void OnUpdate(float p_DeltaTime);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera() { return m_Camera; }
    const OrthographicCamera& GetCamera() const { return m_Camera; }

private:
    bool OnMouseScrolled(const EventMouseScrolled& p_Event);
    bool OnWindowResized(const EventWindowResize& p_Event);

    void CalculateCameraProjection();

    float m_AspectRatio{};
    bool m_CanRotate{};

    float m_ZoomLevel{1.0f};
    float m_ZoomLevelMin{0.25f};
    float m_ZoomLevelMax{100.0f};
    float m_ZoomSensitivity{0.05f};

    OrthographicCamera m_Camera;

    glm::vec3 m_Position{};
    float m_Rotation{};
    float m_TranslationSpeed{1.5f};
    float m_RotationSpeed{45.0f};
};

} // namespace Sonata

#pragma once
#include <format>

#include "events/event.hpp"

namespace Sonata {

class EventMouseMoved final : public Event {
public:
    EventMouseMoved(const float p_X, const float p_Y)
        : m_MouseX(p_X)
        , m_MouseY(p_Y)
    {}

    [[nodiscard]] float GetX() const { return m_MouseX; }
    [[nodiscard]] float GetY() const { return m_MouseY; }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventMouseMoved: {:2}, {:2}", m_MouseX, m_MouseY);
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategory::eInput | EventCategory::eMouse)

private:
    float m_MouseX;
    float m_MouseY;
};

class EventMouseScrolled final : public Event {
public:
    EventMouseScrolled(const float p_X, const float p_Y)
        : m_OffsetX(p_X)
        , m_OffsetY(p_Y)
    {}

    [[nodiscard]] float GetOffsetX() const { return m_OffsetX; }
    [[nodiscard]] float GetOffsetY() const { return m_OffsetY; }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventMouseScrolled: {:2}, {:2}", m_OffsetX, m_OffsetY);
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategory::eInput | EventCategory::eMouse)

private:
    float m_OffsetX;
    float m_OffsetY;
};

class EventMouseButton : public Event {
public:
    [[nodiscard]] int GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategory::eInput | EventCategory::eMouseButton)

protected:
    explicit EventMouseButton(const int p_Button)
        : m_Button(p_Button)
    {}

    int m_Button;
};

class EventMouseButtonPressed final : public EventMouseButton {
public:
    explicit EventMouseButtonPressed(const int p_Button)
        : EventMouseButton(p_Button)
    {}

    [[nodiscard]] std::string ToString() const override { return std::format("EventMouseButtonPressed: {}", m_Button); }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class EventMouseButtonReleased final : public EventMouseButton {
public:
    explicit EventMouseButtonReleased(const int p_Button)
        : EventMouseButton(p_Button)
    {}

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventMouseButtonReleased: {}", m_Button);
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

} // namespace Sonata

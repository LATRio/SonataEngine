#pragma once
#include "events/event.hpp"

#include <format>

namespace Sonata
{

class EventWindowResize final : public Event
{
public:
    EventWindowResize(const int p_Width, const int p_Height)
        : m_Width(p_Width), m_Height(p_Height)
    {

    }

    [[nodiscard]] int GetWidth() const { return m_Width; }
    [[nodiscard]] int GetHeight() const { return m_Height; }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventWindowResize: {}, {}", m_Width, m_Height);
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategory::Application);
private:
    int m_Width;
    int m_Height;
};

class EventWindowClose final : public Event
{
public:
    EventWindowClose() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategory::Application)
};

}
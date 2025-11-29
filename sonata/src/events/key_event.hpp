#pragma once
#include "events/event.hpp"

#include <format>

namespace Sonata
{
class EventKey : public Event
{
public:
    [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

protected:
    explicit EventKey(const int p_Key)
        : m_KeyCode(p_Key) {}

    int m_KeyCode{};
};

class EventKeyPressed final : public EventKey
{
public:
    EventKeyPressed(const int p_KeyCode, const int p_RepeatCount)
        : EventKey(p_KeyCode), m_RepeatCount(p_RepeatCount) {}

    [[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventKeyPressed: {} ({} repeats)", m_KeyCode, m_RepeatCount);
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_RepeatCount{};
};

class EventKeyReleased final : public EventKey
{
public:
    explicit EventKeyReleased(const int p_KeyCode)
        : EventKey(p_KeyCode) {}

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventKeyReleased: {}", m_KeyCode);
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
}

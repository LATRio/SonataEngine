#pragma once
#include <format>

#include "events/event.hpp"
#include "core/input_codes.hpp"

namespace Sonata {

class EventKey : public Event {
public:
    [[nodiscard]] Key GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategory::eInput | EventCategory::eKeyboard)

protected:
    explicit EventKey(const Key p_Key)
        : m_KeyCode(p_Key)
    {}

    Key m_KeyCode{};
};

class EventKeyPressed final : public EventKey {
public:
    EventKeyPressed(const Key p_KeyCode, const int p_RepeatCount)
        : EventKey(p_KeyCode)
        , m_RepeatCount(p_RepeatCount)
    {}

    [[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventKeyPressed: {} ({} repeats)", static_cast<uint32_t>(m_KeyCode), m_RepeatCount);
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_RepeatCount{};
};

class EventKeyReleased final : public EventKey {
public:
    explicit EventKeyReleased(const Key p_KeyCode)
        : EventKey(p_KeyCode)
    {}

    [[nodiscard]] std::string ToString() const override { return std::format("EventKeyReleased: {}", static_cast<uint32_t>(m_KeyCode)); }

    EVENT_CLASS_TYPE(KeyReleased)
};

} // namespace Sonata

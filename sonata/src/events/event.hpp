#pragma once
#include "core.hpp"

namespace Sonata {

enum class EventType
{
    eNone = 0,
    eWindowClose,
    eWindowResize,
    eWindowFocusLost,
    eWindowFocusGained,
    eWindowMoved,
    eWindowMinimize,
    eFramebufferResize,
    eKeyPressed,
    eKeyReleased,
    eMouseButtonPressed,
    eMouseButtonReleased,
    eMouseMoved,
    eMouseScrolled,
};
/* clang-format off */
enum EventCategory
{
    eNone = 0,
    eApplication     = BIT(0),
    eInput           = BIT(1),
    eKeyboard        = BIT(2),
    eMouse           = BIT(3),
    eMouseButton     = BIT(4),
};

#define EVENT_CLASS_TYPE(type)                                              \
static EventType GetStaticType() { return EventType::e##type; }             \
virtual EventType GetEventType() const override { return GetStaticType(); } \
virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
/* clang-format on */
// TODO: Test with std::variant
class Event {
    friend class EventDispatcher;

public:
    virtual ~Event() = default;

    bool Handled{};

    [[nodiscard]] virtual EventType GetEventType() const = 0;
    [[nodiscard]] virtual const char* GetName() const = 0;
    [[nodiscard]] virtual int GetCategoryFlags() const = 0;
    [[nodiscard]] virtual std::string ToString() const { return GetName(); }

    [[nodiscard]] bool IsInCategory(const EventCategory p_Category) const
    {
        return GetCategoryFlags() & static_cast<int>(p_Category);
    }
};

class EventDispatcher {
    template <typename T>
    using EventFn = std::function<bool(T&)>;

public:
    explicit EventDispatcher(Event& p_Event)
        : m_Event(p_Event)
    {}

    template <typename T>
    bool Dispatch(EventFn<T> p_Func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled |= p_Func(*static_cast<T*>(&m_Event));
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

} // namespace Sonata

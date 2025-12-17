#pragma once
#include <format>

#include "events/event.hpp"

namespace Sonata {

class EventWindowResize final : public Event {
public:
    EventWindowResize(const int p_Width, const int p_Height)
        : m_Width(p_Width)
        , m_Height(p_Height)
    {}

    [[nodiscard]] int GetWidth() const { return m_Width; }
    [[nodiscard]] int GetHeight() const { return m_Height; }
    [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventWindowResize: {}, {}", m_Width, m_Height);
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategory::eApplication)

private:
    int m_Width;
    int m_Height;
};

class EventWindowMinimize final : public Event {
public:
    explicit EventWindowMinimize(const bool p_Minimized)
        : m_Minimized(p_Minimized)
    {}

    [[nodiscard]] bool IsMinimized() const { return m_Minimized; }

    [[nodiscard]] std::string ToString() const override { return std::format("EventWindowMinimize: {}", m_Minimized); }

    EVENT_CLASS_TYPE(WindowMinimize)
    EVENT_CLASS_CATEGORY(EventCategory::eApplication)

private:
    bool m_Minimized{};
};

class EventWindowClose final : public Event {
public:
    EventWindowClose() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategory::eApplication)
};

class EventFramebufferResize final : public Event {
public:
    EventFramebufferResize(const int p_Width, const int p_Height)
        : m_Width(p_Width)
        , m_Height(p_Height)
    {}

    [[nodiscard]] int GetWidth() const { return m_Width; }
    [[nodiscard]] int GetHeight() const { return m_Height; }
    [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

    [[nodiscard]] std::string ToString() const override
    {
        return std::format("EventFramebufferResize: {}, {}", m_Width, m_Height);
    }

    EVENT_CLASS_TYPE(FramebufferResize)
    EVENT_CLASS_CATEGORY(EventCategory::eApplication)

private:
    int m_Width;
    int m_Height;
};

} // namespace Sonata

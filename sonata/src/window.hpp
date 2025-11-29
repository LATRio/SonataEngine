#pragma once
#include "events/event.hpp"

class GLFWwindow;

namespace Sonata
{

struct WindowProps
{
    int m_Width{}, m_Height{};
    std::string_view m_Title{};
    bool m_VSync{};
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window() = delete;
    explicit Window(const WindowProps& p_Props);
    ~Window();

    void Update();

    [[nodiscard]] bool GetWindowShouldClose() const;
    void SetWindowShouldClose(int p_Value) const;

    void SetEventCallback(const EventCallbackFn &p_Callback);
    void SetVSync(bool p_Enable);
    [[nodiscard]] bool IsVSync() const;

private:
    GLFWwindow* m_Window{};

    struct WindowData
    {
        int m_Width{}, m_Height{};
        std::string_view m_Title{};
        bool m_VSync{};

        EventCallbackFn m_Callback{};
    } m_WindowData{};
};

}
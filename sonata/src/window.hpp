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

    void PollEvents();
    void SwapBuffers();

    void SetEventCallback(const EventCallbackFn &p_Callback);
    void SetVSync(bool p_Enable);
    [[nodiscard]] bool IsVSync() const;

    [[nodiscard]] int GetWidth() const { return m_WindowData.m_Width; }
    [[nodiscard]] int GetHeight() const { return m_WindowData.m_Height; }

    template<typename T>
    T GetWidth() const { return static_cast<T>(m_WindowData.m_Width); }
    template<typename T>
    T GetHeight() const { return static_cast<T>(m_WindowData.m_Height); }

    [[nodiscard]] GLFWwindow* GetNativeWindow() { return m_Window; };

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
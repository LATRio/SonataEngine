#pragma once
#include "events/event.hpp"

struct GLFWwindow;

namespace Sonata {
class RenderContext;

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

    void PollEvents() const;
    void SwapBuffers() const;

    void SetEventCallback(const EventCallbackFn& p_Callback);
    void SetVSync(bool p_Enable);
    [[nodiscard]] bool IsVSync() const;

    [[nodiscard]] int GetWidth() const { return m_WindowData.m_Width; }
    [[nodiscard]] int GetHeight() const { return m_WindowData.m_Height; }
    /* clang-format off */
    template <typename T>
    T GetWidth() const { return static_cast<T>(m_WindowData.m_Width); }
    template <typename T>
    T GetHeight() const { return static_cast<T>(m_WindowData.m_Height); }
    /* clang-format on */
    [[nodiscard]] GLFWwindow* GetNativeWindow() const { return m_Window; };

private:
    GLFWwindow* m_Window{};
    Scope<RenderContext> m_RenderContext;

    struct WindowData
    {
        int m_Width{};
        int m_Height{};
        std::string_view m_Title{};
        bool m_VSync{};

        EventCallbackFn m_Callback{};
    } m_WindowData{};
};

} // namespace Sonata

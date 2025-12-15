#pragma once
#include <memory>

#include "../events/app_event.hpp"
#include "../layers/imgui_layer.hpp"
#include "../layers/layer_stack.hpp"
#include "window.hpp"

namespace Sonata {

class Window;
class EventWindowClose;
class EventFramebufferResize;

class Application {
public:
    Application();
    virtual ~Application() = default;

    // TODO: Add support for Unicode
    [[maybe_unused]] virtual void Init(const WindowProps& p_Props);
    [[maybe_unused]] void Loop();

    void OnEvent(Event& p_Event);
    bool OnWindowClosed(const EventWindowClose& p_Event);
    bool OnWindowMinimized(const EventWindowMinimize& p_Event);
    bool OnFramebufferResize(const EventFramebufferResize& p_Event) const;

    void PushLayer(Layer* p_Layer);
    void PushOverlay(Layer* p_Layer);

    void Shutdown();

    [[nodiscard]] Window* GetWindow() const { return m_Window.get(); }

    static Application* GetInstance() { return s_Instance; }

private:
    static Application* s_Instance;

    Scope<Window> m_Window;
    LayerStack m_LayerStack;
    bool m_IsRunning{true};
    bool m_IsMinimized{false};

    ImGuiLayer* m_ImGuiLayer{};

    float m_LastFrameTime;
};

} // namespace Sonata

#pragma once
#include <memory>
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
#endif
#include <SDL3/SDL.h>
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include "events/app_event.hpp"
#include "layers/imgui_layer.hpp"
#include "layers/layer_stack.hpp"
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
    SDL_AppResult Loop();

    void OnEvent(Event& p_Event);
    [[nodiscard]] bool OnWindowClosed(const EventWindowClose& p_Event);
    [[nodiscard]] bool OnWindowMinimized(const EventWindowMinimize& p_Event);
    [[nodiscard]] bool OnFramebufferResize(const EventFramebufferResize& p_Event) const;

    void PushLayer(Layer* p_Layer);
    void PushOverlay(Layer* p_Layer);

    void Shutdown();

    [[nodiscard]] Window* GetWindow() const { return m_Window.get(); }

    static Application* GetInstance() { return s_Instance; }

private:
    static Application* s_Instance;

    Scope<Window> m_Window;
    LayerStack m_LayerStack;
    SDL_AppResult m_LoopState{SDL_APP_CONTINUE};
    bool m_IsMinimized{false};

    ImGuiLayer* m_ImGuiLayer{};

    float m_LastFrameTime;
};

} // namespace Sonata

#pragma once
#include <memory>
#include <string_view>

#include "layers/imgui_layer.hpp"
#include "layers/layer_stack.hpp"
#include "window.hpp"

namespace Sonata {

class Window;
class EventWindowClose;
class Shader;
class VertexArray;
class VertexBuffer;
class IndexBuffer;

class Application {
public:
    Application();
    virtual ~Application();

    // TODO: Add support for Unicode
    [[maybe_unused]] virtual void Init(int p_Width, int p_Height, std::string_view p_Title);
    [[maybe_unused]] void Loop();

    void OnEvent(Event& p_Event);
    bool OnWindowClosed(const EventWindowClose& p_Event);

    void PushLayer(Layer* p_Layer);
    void PushOverlay(Layer* p_Layer);

    void Shutdown();

    [[nodiscard]] Window* GetWindow() const { return m_Window.get(); }

    static Application* GetInstance() { return s_Instance; }

private:
    static Application* s_Instance;

    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;
    bool m_IsRunning{true};

    ImGuiLayer* m_ImGuiLayer{};

    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<VertexArray> m_VertexArray;

    std::unique_ptr<Shader> m_SquareShader;
    std::unique_ptr<VertexArray> m_SquareVA;
};

} // namespace Sonata

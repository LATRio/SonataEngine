#include "sandbox.hpp"

#include "events/key_event.hpp"
#include "input.hpp"
#include "input_codes.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <imgui.h>
#pragma GCC diagnostic pop

class ExampleLayer final : public Sonata::Layer
{
public:
    ExampleLayer()
        : Layer("ExampleLayer") {}
    ~ExampleLayer() override = default;

    void OnImGuiRender() override
    {
        using namespace ImGui;

        Begin("Example");
        Text("Hello World!");
        End();
    }

    void OnUpdate() override
    {
        if (Sonata::Input::IsKeyPressed(SN_KEY_SPACE))
        {
            SN_APP_TRACE("Space is pressed");
        }
    }

    void OnEvent(Event& p_Event) override
    {
        if (p_Event.GetEventType() == EventType::KeyPressed)
        {
            const auto& ev = static_cast<Sonata::EventKeyPressed&>(p_Event);
            if (ev.GetKeyCode() == SN_KEY_ESCAPE)
            {
                Sonata::Application::GetInstance()->Shutdown();
            }
            else if (ev.GetKeyCode() == SN_KEY_1)
            {
            }
        }
    }
};

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}

void Sandbox::Init(int p_Width, int p_Height, std::string_view p_Title)
{
    Application::Init(p_Width, p_Height, p_Title);

    PushLayer(new ExampleLayer());
}
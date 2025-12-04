#include "sandbox.hpp"

#include "events/key_event.hpp"
#include "input.hpp"
#include "input_codes.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wsign-conversion"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/string_cast.hpp>

#pragma GCC diagnostic pop

#include <imgui.h>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

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
                const glm::mat4 mat = camera(0.0f, glm::vec2(0.0f, 0.0f));
                SN_APP_INFO("{}", glm::to_string(mat).c_str());
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
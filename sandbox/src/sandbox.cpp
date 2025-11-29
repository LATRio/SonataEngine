#include "sandbox.hpp"

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}

void Sandbox::Init(int p_Width, int p_Height, std::string_view p_Title)
{
    Application::Init(p_Width, p_Height, p_Title);

    PushOverlay(new Sonata::ImGuiLayer());
}
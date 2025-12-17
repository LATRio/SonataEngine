#include "sandbox.hpp"
#include <core/entry_point.hpp>

#include "sandbox_2d.hpp"

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}

void Sandbox::Init(const Sonata::WindowProps& p_Props)
{
    Application::Init(p_Props);

    PushLayer(new Sandbox2D());
}

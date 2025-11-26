#include "application.h"
#include <GLFW/glfw3.h>

#include "window.h"

namespace Sonata {

Application::Application()
{
}

Application::~Application()
{
}

void Application::InitWindow(int p_Width, int p_Height, std::string_view title)
{
    m_Window = std::make_unique<Window>(p_Width, p_Height, title);
}

void Application::Loop()
{
    while (!m_Window->GetWindowShouldClose())
    {
        if (m_Window->IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            m_Window->SetWindowShouldClose(GLFW_TRUE);
        }
        if (m_Window->IsKeyPressed(GLFW_KEY_SPACE))
        {
            m_Event.Execute();
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->Update();
    }
}

} // Sonata
#include "application.h"

#include "window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Sonata {

Application::Application()
{
    m_Event.AddBind(std::bind(&Application::Print, this), this);
}

Application::~Application()
{
}

void Application::InitWindow(int p_Width, int p_Height, std::string_view title)
{
    m_Window = std::make_unique<Window>(p_Width, p_Height, title);
    m_Event.AddBind(std::bind(&Window::Print, m_Window.get()), m_Window.get());
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

void Application::Print()
{
    std::cout << "event worked" << std::endl;
}

} // Sonata
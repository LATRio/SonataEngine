#include "window.h"

#include "glad/gl.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "log.h"

namespace Sonata
{

static bool glfwInitialized = false;

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const int p_Width, const int p_Height, std::string_view p_Title)
{
    if (!glfwInitialized)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            SN_ENGINE_FATAL("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwInitialized = true;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef SONATA_DEBUG
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GL_TRUE);
#endif

        int major_version;
        int minor_version;
        glfwGetVersion(&major_version, &minor_version, nullptr);
        SN_ENGINE_INFO("Window Initialized! (powered by glfw-{}.{})", major_version, minor_version);
        SN_ENGINE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    m_Window = glfwCreateWindow(p_Width, p_Height, p_Title.data(), nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        SN_ENGINE_FATAL("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window!");
    }
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate();
        SN_ENGINE_FATAL("Failed to initialize GLAD");
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::GetWindowShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}
void Window::SetWindowShouldClose(const int value) const
{
    glfwSetWindowShouldClose(m_Window, value);
}
void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::IsKeyPressed(const int key) const
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

} // namespace
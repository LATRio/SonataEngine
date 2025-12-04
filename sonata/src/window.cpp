#include "window.hpp"
#include "events/app_event.hpp"
#include "events/key_event.hpp"
#include "events/mouse_event.hpp"
#include "rendering/opengl/opengl_context.hpp"

namespace Sonata
{

static bool glfwInitialized = false;

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *p_Window, const int p_Width, const int p_Height)
{
    glViewport(0, 0, p_Width, p_Height);
}

void GLFWErrorCallback(int error_code, const char* description)
{
    SN_ENGINE_FATAL("GLFW Error ({}): {}", error_code, description);
}

Window::Window(const WindowProps &p_Props)
{
    if (!glfwInitialized)
    {
        const int success = glfwInit();
        SN_ASSERT_MSG(success, "Failed to initialize GLFW3");
        glfwSetErrorCallback(GLFWErrorCallback);
        glfwInitialized = true;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GL_TRUE);

        int major_version;
        int minor_version;
        glfwGetVersion(&major_version, &minor_version, nullptr);
        SN_ENGINE_INFO("Window Initialized! (powered by glfw-{}.{})", major_version, minor_version);
    }

    m_WindowData = {
        p_Props.m_Width,
        p_Props.m_Height,
        p_Props.m_Title,
        p_Props.m_VSync
    };

    m_Window = glfwCreateWindow(
        m_WindowData.m_Width,
        m_WindowData.m_Height,
        m_WindowData.m_Title.data(),
        nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        SN_ENGINE_FATAL("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window!");
    }
    m_RenderContext = std::make_unique<OpenGLContext>(m_Window);
    m_RenderContext->Init();

    glfwSetWindowUserPointer(m_Window, &m_WindowData);
    SetVSync(m_WindowData.m_VSync);

    glViewport(0, 0, m_WindowData.m_Width, m_WindowData.m_Height);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        m_Data.m_Width = width;
        m_Data.m_Height = height;

        EventWindowResize event(width, height);
        m_Data.m_Callback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        const WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        EventWindowClose event;
        m_Data.m_Callback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        const WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_RELEASE: {
            EventKeyReleased event(key);
            m_Data.m_Callback(event);
            break;
        }
        case GLFW_PRESS: {
            EventKeyPressed event(key, 0);
            m_Data.m_Callback(event);
            break;
        }
        case GLFW_REPEAT: {
            EventKeyPressed event(key, 1);
            m_Data.m_Callback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        const WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_RELEASE: {
            EventMouseButtonReleased event(button);
            m_Data.m_Callback(event);
            break;
        }
        case GLFW_PRESS: {
            EventMouseButtonPressed event(button);
            m_Data.m_Callback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        const WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        EventMouseScrolled event(xOffset, yOffset);
        m_Data.m_Callback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        const WindowData& m_Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        EventMouseMoved event(xPos, yPos);
        m_Data.m_Callback(event);
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
#if GLFW_VERSION_MAJOR <= 3 && GLFW_VERSION_MINOR < 5
    glfwPollEvents();
#endif
    glfwTerminate();
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    m_RenderContext->SwapBuffers();
}

void Window::SetEventCallback(const EventCallbackFn &p_Callback)
{
    m_WindowData.m_Callback = p_Callback;
}

void Window::SetVSync(const bool p_Enable)
{
    if (p_Enable)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
    m_WindowData.m_VSync = p_Enable;
}

bool Window::IsVSync() const
{
    return m_WindowData.m_VSync;
}

} // namespace
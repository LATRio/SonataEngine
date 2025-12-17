#include "window.hpp"
#include "../events/app_event.hpp"
#include "../events/key_event.hpp"
#include "../events/mouse_event.hpp"
#include "../rendering/opengl/opengl_context.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata
{

static bool glfwInitialized = false;

void GLFWErrorCallback(int p_ErrorCode, const char* p_Description)
{
    SN_ENGINE_FATAL("GLFW Error ({}): {}", p_ErrorCode, p_Description);
}

Window::Window(const WindowProps &p_Props)
{
    SN_PROFILE_FUNCTION();
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

    {
        SN_PROFILE_SCOPE("glfwCreateWindow");
        m_Window = glfwCreateWindow(
            m_WindowData.m_Width,
            m_WindowData.m_Height,
            m_WindowData.m_Title.data(),
            nullptr, nullptr);
        if (!m_Window)
        {
            glfwTerminate();
            SN_ENGINE_FATAL("Failed to create GLFW window");
        }
    }

    m_RenderContext = CreateScope<OpenGLContext>(m_Window);
    m_RenderContext->Init();

    glfwSetWindowUserPointer(m_Window, &m_WindowData);
    SetVSync(m_WindowData.m_VSync);

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *p_Window, const int p_Width, const int p_Height)
    {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        EventFramebufferResize event{p_Width, p_Height};
        data.m_Callback(event);
    });

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *p_Window, const int p_Width, const int p_Height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));
        data.m_Width = p_Width;
        data.m_Height = p_Height;

        EventWindowResize event(p_Width, p_Height);
        data.m_Callback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *p_Window) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        EventWindowClose event;
        data.m_Callback(event);
    });

    glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *p_Window, const int p_Iconified) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        EventWindowMinimize event(p_Iconified);
        data.m_Callback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *p_Window, const int p_Key, const int p_Scancode, const int p_Action, const int p_Mods) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        switch (p_Action)
        {
        case GLFW_RELEASE: {
            EventKeyReleased event(p_Key);
            data.m_Callback(event);
            break;
        }
        case GLFW_PRESS: {
            EventKeyPressed event(p_Key, 0);
            data.m_Callback(event);
            break;
        }
        case GLFW_REPEAT: {
            EventKeyPressed event(p_Key, 1);
            data.m_Callback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *p_Window, const int p_Button, const int p_Action, const int p_Mods) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        switch (p_Action)
        {
        case GLFW_RELEASE: {
            EventMouseButtonReleased event(p_Button);
            data.m_Callback(event);
            break;
        }
        case GLFW_PRESS: {
            EventMouseButtonPressed event(p_Button);
            data.m_Callback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *p_Window, const double p_OffsetX, const double p_OffsetY) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        EventMouseScrolled event(static_cast<float>(p_OffsetX), static_cast<float>(p_OffsetY));
        data.m_Callback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *p_Window, const double p_PosX, const double p_PosY) {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_Window));

        EventMouseMoved event(static_cast<float>(p_PosX), static_cast<float>(p_PosY));
        data.m_Callback(event);
    });
}

Window::~Window()
{
    SN_PROFILE_FUNCTION();
    glfwDestroyWindow(m_Window);
#if GLFW_VERSION_MAJOR <= 3 && GLFW_VERSION_MINOR < 5
    glfwPollEvents();
#endif
    glfwTerminate();
}

void Window::PollEvents() const
{
    SN_PROFILE_FUNCTION();
    glfwPollEvents();
}

void Window::SwapBuffers() const
{
    SN_PROFILE_FUNCTION();
    m_RenderContext->SwapBuffers();
}

void Window::SetEventCallback(const EventCallbackFn &p_Callback)
{
    m_WindowData.m_Callback = p_Callback;
}

void Window::SetVSync(const bool p_Enable)
{
    SN_PROFILE_FUNCTION();
    glfwSwapInterval(p_Enable ? 1 : 0);
    m_WindowData.m_VSync = p_Enable;
}

bool Window::IsVSync() const
{
    return m_WindowData.m_VSync;
}

}

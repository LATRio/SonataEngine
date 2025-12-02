#include "window.hpp"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "events/app_event.hpp"
#include "events/key_event.hpp"
#include "events/mouse_event.hpp"
#include "logger/log.hpp"

namespace Sonata
{

static bool glfwInitialized = false;

// TODO: Use proper level of severity for logger
void APIENTRY glDebugOutput(GLenum p_Source,
                            GLenum p_Type,
                            unsigned int p_Id,
                            GLenum p_Severity,
                            [[maybe_unused]] GLsizei p_Length,
                            const char *p_Message,
                            [[maybe_unused]] const void *p_UserParam)
{
    // ignore non-significant error/warning codes
    if(p_Id == 131169 || p_Id == 131185 || p_Id == 131218 || p_Id == 131204) return;

    SN_ENGINE_ERR("---------------");
    SN_ENGINE_ERR("Debug message ({}): {}", p_Id, p_Message);

    switch (p_Source)
    {
        case GL_DEBUG_SOURCE_API:             SN_ENGINE_ERR("Source: API"); break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   SN_ENGINE_ERR("Source: Window System"); break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: SN_ENGINE_ERR("Source: Shader Compiler"); break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     SN_ENGINE_ERR("Source: Third Party"); break;
        case GL_DEBUG_SOURCE_APPLICATION:     SN_ENGINE_ERR("Source: Application"); break;
        case GL_DEBUG_SOURCE_OTHER:           SN_ENGINE_ERR("Source: Other"); break;
    	default: SN_ENGINE_ERR("Source: Unknown"); break;
    }

    switch (p_Type)
    {
        case GL_DEBUG_TYPE_ERROR:               SN_ENGINE_ERR("Type: Error"); break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: SN_ENGINE_ERR("Type: Deprecated Behaviour"); break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  SN_ENGINE_ERR("Type: Undefined Behaviour"); break;
        case GL_DEBUG_TYPE_PORTABILITY:         SN_ENGINE_ERR("Type: Portability"); break;
        case GL_DEBUG_TYPE_PERFORMANCE:         SN_ENGINE_ERR("Type: Performance"); break;
        case GL_DEBUG_TYPE_MARKER:              SN_ENGINE_ERR("Type: Marker"); break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          SN_ENGINE_ERR("Type: Push Group"); break;
        case GL_DEBUG_TYPE_POP_GROUP:           SN_ENGINE_ERR("Type: Pop Group"); break;
        case GL_DEBUG_TYPE_OTHER:               SN_ENGINE_ERR("Type: Other"); break;
    	default: SN_ENGINE_ERR("Type: Unknown"); break;
    }

    switch (p_Severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SN_ENGINE_ERR("Severity: high"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       SN_ENGINE_ERR("Severity: medium"); break;
        case GL_DEBUG_SEVERITY_LOW:          SN_ENGINE_ERR("Severity: low"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SN_ENGINE_ERR("Severity: notification"); break;
    	default: SN_ENGINE_ERR("Severity: Unknown"); break;
    }
    SN_ENGINE_ERR("---------------");
}

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
    glfwMakeContextCurrent(m_Window);

    const int success = gladLoadGL(glfwGetProcAddress);
    SN_ASSERT_MSG(success, "Failed to initialize GLAD");

    glfwSetWindowUserPointer(m_Window, &m_WindowData);
    SetVSync(m_WindowData.m_VSync);

    glViewport(0, 0, m_WindowData.m_Width, m_WindowData.m_Height);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    SN_ENGINE_INFO("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    {
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }
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
    glfwSwapBuffers(m_Window);
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
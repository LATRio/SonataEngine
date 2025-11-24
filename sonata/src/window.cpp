#include "window.h"

#include "glad/gl.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "log.h"

namespace Sonata
{

static bool glfwInitialized = false;

// TODO: Use proper level of severity for logger
void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            [[maybe_unused]] GLsizei length,
                            const char *message,
                            [[maybe_unused]] const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    SN_ENGINE_ERR("---------------");
    SN_ENGINE_ERR("Debug message ({}): {}", id, message);

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             SN_ENGINE_ERR("Source: API"); break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   SN_ENGINE_ERR("Source: Window System"); break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: SN_ENGINE_ERR("Source: Shader Compiler"); break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     SN_ENGINE_ERR("Source: Third Party"); break;
        case GL_DEBUG_SOURCE_APPLICATION:     SN_ENGINE_ERR("Source: Application"); break;
        case GL_DEBUG_SOURCE_OTHER:           SN_ENGINE_ERR("Source: Other"); break;
    	default: SN_ENGINE_ERR("Source: Unknown"); break;
    }

    switch (type)
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

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SN_ENGINE_ERR("Severity: high"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       SN_ENGINE_ERR("Severity: medium"); break;
        case GL_DEBUG_SEVERITY_LOW:          SN_ENGINE_ERR("Severity: low"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SN_ENGINE_ERR("Severity: notification"); break;
    	default: SN_ENGINE_ERR("Severity: Unknown"); break;
    }
    SN_ENGINE_ERR("---------------");
}

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
    SN_ENGINE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    {
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }

    glViewport(0, 0, p_Width, p_Height);
    // TODO: Event system might make things easier
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
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
void Window::Print()
{
    SN_ENGINE_INFO("Printing window");
}

} // namespace
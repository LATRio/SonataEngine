#include "opengl_context.hpp"
#include "core.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata {

/* clang-format off */
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

    std::stringstream ss;

    ss << "\n---------------\n";
    ss << std::format("Debug message ({}): {}\n", p_Id, p_Message);

    switch (p_Source)
    {
        case GL_DEBUG_SOURCE_API:             ss << ("Source: API\n"); break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   ss << ("Source: Window System\n"); break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: ss << ("Source: Shader Compiler\n"); break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     ss << ("Source: Third Party\n"); break;
        case GL_DEBUG_SOURCE_APPLICATION:     ss << ("Source: Application\n"); break;
        case GL_DEBUG_SOURCE_OTHER:           ss << ("Source: Other\n"); break;
    	default: ss << ("Source: Unknown\n"); break;
    }

    switch (p_Type)
    {
        case GL_DEBUG_TYPE_ERROR:               ss << ("Type: Error\n"); break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ss << ("Type: Deprecated Behaviour\n"); break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  ss << ("Type: Undefined Behaviour\n"); break;
        case GL_DEBUG_TYPE_PORTABILITY:         ss << ("Type: Portability\n"); break;
        case GL_DEBUG_TYPE_PERFORMANCE:         ss << ("Type: Performance\n"); break;
        case GL_DEBUG_TYPE_MARKER:              ss << ("Type: Marker\n"); break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          ss << ("Type: Push Group\n"); break;
        case GL_DEBUG_TYPE_POP_GROUP:           ss << ("Type: Pop Group\n"); break;
        case GL_DEBUG_TYPE_OTHER:               ss << ("Type: Other\n"); break;
    	default: ss << ("Type: Unknown\n"); break;
    }

    switch (p_Severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         ss << ("Severity: high\n"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       ss << ("Severity: medium\n"); break;
        case GL_DEBUG_SEVERITY_LOW:          ss << ("Severity: low\n"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: ss << ("Severity: notification\n"); break;
    	default: ss << ("Severity: Unknown\n"); break;
    }
    ss << ("---------------");

    switch (p_Severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SN_ENGINE_FATAL(ss.str()); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       SN_ENGINE_ERR(ss.str()); break;
        case GL_DEBUG_SEVERITY_LOW:          SN_ENGINE_WARN(ss.str()); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SN_ENGINE_INFO(ss.str()); break;
        default: SN_ENGINE_TRACE(ss.str()); break;
    }
}
/* clang-format on */

void OpenGLContext::Init()
{
    SN_PROFILE_FUNCTION();

    glfwMakeContextCurrent(m_Window);

    const int success = gladLoadGL(glfwGetProcAddress);
    SN_ASSERT_MSG(success, "Failed to initialize GLAD");

    SN_ENGINE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
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
}

void OpenGLContext::SwapBuffers()
{
    SN_PROFILE_FUNCTION();

    glfwSwapBuffers(m_Window);
}

} // namespace Sonata

#pragma once
#include "rendering/render_context.hpp"

namespace Sonata {

class OpenGLContext final : public RenderContext {
public:
    explicit OpenGLContext(GLFWwindow* p_Window)
        : RenderContext(p_Window)
    {}
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffers() override;
};

} // namespace Sonata

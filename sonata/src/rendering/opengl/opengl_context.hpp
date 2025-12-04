#pragma once
#include "../render_context.hpp"

namespace Sonata {

class OpenGLContext final : public RenderContext {
public:
    explicit OpenGLContext(GLFWwindow* p_window)
        : RenderContext(p_window) {}
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffers() override;
};

}

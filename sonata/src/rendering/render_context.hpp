#pragma once

class GLFWwindow;

namespace Sonata {

class RenderContext {
public:
    explicit RenderContext(GLFWwindow* p_window)
        : m_Window(p_window) {}
    virtual ~RenderContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

protected:
    GLFWwindow* m_Window;
};

}

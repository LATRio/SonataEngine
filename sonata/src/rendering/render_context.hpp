#pragma once

class GLFWwindow;

namespace Sonata {

class RenderContext {
public:
    explicit RenderContext(GLFWwindow* p_Window)
        : m_Window(p_Window) {}
    virtual ~RenderContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

protected:
    GLFWwindow* m_Window;
};

}

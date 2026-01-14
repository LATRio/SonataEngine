#pragma once

struct GLFWwindow;

namespace Sonata {

class RenderContext {
public:
    explicit RenderContext(GLFWwindow* p_Window)
        : m_Window(p_Window)
    {}
    virtual ~RenderContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

    static Scope<RenderContext> Create(GLFWwindow* p_Window);

protected:
    GLFWwindow* m_Window;
};

} // namespace Sonata

#pragma once
#include "rendering/render_context.hpp"

namespace Sonata {

class OpenGLContext final : public RenderContext {
public:
    explicit OpenGLContext(SDL_Window* p_Window)
        : RenderContext(p_Window)
    {}
    ~OpenGLContext() override;

    void Init() override;
    void SwapBuffers() override;
    void SetSwapInterval(int p_Interval) override;

private:
    SDL_GLContext m_Context{};
};

} // namespace Sonata

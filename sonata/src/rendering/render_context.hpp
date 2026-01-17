#pragma once

struct SDL_Window;

namespace Sonata {

class RenderContext {
public:
    explicit RenderContext(SDL_Window* p_Window)
        : m_Window(p_Window)
    {}
    virtual ~RenderContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetSwapInterval(int p_Interval) = 0;

    static Scope<RenderContext> Create(SDL_Window* p_Window);

protected:
    SDL_Window* m_Window;
};

} // namespace Sonata

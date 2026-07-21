#pragma once
#include "rendering/render_context.hpp"

namespace Sonata {

class VulkanContext final : public RenderContext {
public:
    explicit VulkanContext(SDL_Window* p_Window)
        : RenderContext(p_Window)
    {}
    ~VulkanContext() override;

    void Init() override;
    void SwapBuffers() override;
    void SetSwapInterval(int p_Interval) override;

private:

};

} // Sonata

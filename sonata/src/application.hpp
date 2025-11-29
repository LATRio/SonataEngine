#pragma once
#include "window.hpp"

#include <memory>
#include <string_view>

namespace Sonata {
class Window;

class Application {
public:
    Application();
    virtual ~Application();

    // TODO: Add support for Unicode
    [[maybe_unused]] void InitWindow(int p_Width, int p_Height, std::string_view p_Title);
    [[maybe_unused]] void Loop() const;

    void OnEvent(const Event & p_Event);

private:
    std::unique_ptr<Window> m_Window;
    bool m_IsRunning{true};
};

} // Sonata

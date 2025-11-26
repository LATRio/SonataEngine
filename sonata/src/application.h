#pragma once
#include <memory>
#include <string_view>

#include "events/event.h"

namespace Sonata {
class Window;

class Application {
public:
    Application();
    virtual ~Application();

    // TODO: Add support for Unicode
    // TODO: Pass struct with window settings instead
    [[maybe_unused]] void InitWindow(int p_Width, int p_Height, std::string_view title);
    [[maybe_unused]] void Loop();

private:
    std::unique_ptr<Window> m_Window;

    Event<void()> m_Event;
};

} // Sonata

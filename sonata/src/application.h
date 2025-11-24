#pragma once
#include "events/event.h"

#include <memory>

namespace Sonata {
class Window;

class Application {
public:
    Application();
    virtual ~Application();

    // TODO: Add support for Unicode
    // TODO: Pass struct with window settings instead
    void InitWindow(int p_Width, int p_Height, std::string_view title);
    void Loop();
    void Print();

private:
    std::unique_ptr<Window> m_Window;

    Event<void()> m_Event;
};

} // Sonata

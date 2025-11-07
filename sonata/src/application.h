#pragma once
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

private:
    std::unique_ptr<Window> m_Window;
};

} // Sonata

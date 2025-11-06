#pragma once

class GLFWwindow;

namespace Sonata
{

class Window {
public:
    Window();
    ~Window();

private:
    GLFWwindow* m_Window;
};

}
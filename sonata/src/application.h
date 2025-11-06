#pragma once

class GLFWwindow;

namespace Sonata {

class Application {
public:
    Application();
    ~Application();

    void Loop();

private:
    GLFWwindow* window;
};

} // Sonata

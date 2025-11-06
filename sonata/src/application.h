#pragma once

class GLFWwindow;

namespace Sonata {

class Application {
public:
    Application();
    virtual ~Application();

    void Loop();

private:
    GLFWwindow* window;
};

} // Sonata

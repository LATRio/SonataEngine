#pragma once
#include <string_view>

struct GLFWwindow;

namespace Sonata
{

class Window {
public:
    Window(int p_Width, int p_Height, std::string_view p_Title);
    ~Window();

    [[nodiscard]] bool GetWindowShouldClose() const;
    void SetWindowShouldClose(int value) const;

    void Update();

    [[nodiscard]] bool IsKeyPressed(int key) const;

    void Print();
private:
    GLFWwindow* m_Window;
};

}
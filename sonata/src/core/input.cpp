#include "input.hpp"

#include "application.hpp"
#include "profiler/instrumentor.hpp"

namespace Sonata {

bool Input::IsKeyPressed(const int p_Key)
{
    SN_PROFILE_FUNCTION();

    GLFWwindow* window = Application::GetInstance()->GetWindow()->GetNativeWindow();
    return glfwGetKey(window, p_Key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(const int p_Button)
{
    SN_PROFILE_FUNCTION();

    GLFWwindow* window = Application::GetInstance()->GetWindow()->GetNativeWindow();
    return glfwGetMouseButton(window, p_Button) == GLFW_PRESS;
}

double Input::GetCursorX()
{
    auto [x, y] = GetCursorPosition();
    return x;
}

double Input::GetCursorY()
{
    auto [x, y] = GetCursorPosition();
    return y;
}
std::pair<double, double> Input::GetCursorPosition()
{
    SN_PROFILE_FUNCTION();

    GLFWwindow* window = Application::GetInstance()->GetWindow()->GetNativeWindow();
    std::pair<double, double> pos;
    glfwGetCursorPos(window, &pos.first, &pos.second);
    return pos;
}

} // namespace Sonata

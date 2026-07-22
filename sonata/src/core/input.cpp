#include "input.hpp"

#include "application.hpp"
#include "profiler/instrumentor.hpp"

#include <SDL3/SDL.h>

namespace Sonata {

bool Input::IsKeyPressed(Key p_Key)
{
    SN_PROFILE_FUNCTION;

    const bool* states{SDL_GetKeyboardState(nullptr)};
    return states[SDL_GetScancodeFromKey(static_cast<uint32_t>(p_Key), nullptr)];
}

bool Input::IsMouseButtonPressed(MouseButton p_Button)
{
    SN_PROFILE_FUNCTION;

    return SDL_GetMouseState(nullptr, nullptr) & static_cast<SDL_MouseButtonFlags>(p_Button);
}

float Input::GetCursorX()
{
    auto [x, y] = GetCursorPosition();
    return x;
}

float Input::GetCursorY()
{
    auto [x, y] = GetCursorPosition();
    return y;
}
std::pair<float, float> Input::GetCursorPosition()
{
    SN_PROFILE_FUNCTION;

    std::pair<float, float> pos;
    SDL_GetMouseState(&pos.first, &pos.second);
    return pos;
}

} // namespace Sonata

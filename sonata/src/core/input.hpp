#pragma once
#include "input_codes.hpp"

namespace Sonata {

class Input {
public:
    static bool IsKeyPressed(Key p_Key);
    static bool IsMouseButtonPressed(MouseButton p_Button);
    static float GetCursorX();
    static float GetCursorY();
    static std::pair<float, float> GetCursorPosition();
};

} // namespace Sonata

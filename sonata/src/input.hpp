#pragma once
#include "input_codes.hpp"

namespace Sonata {

class Input {
public:
    static bool IsKeyPressed(int p_Key);
    static bool IsMouseButtonPressed(int p_Button);
    static double GetCursorX();
    static double GetCursorY();
    static std::pair<double, double> GetCursorPosition();
};

}

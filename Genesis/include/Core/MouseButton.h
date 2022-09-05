#pragma once

#include <cstdint>

namespace Genesis
{
    enum class MouseButton : uint64_t
    {
        BUTTON_1 = 0,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4,
        BUTTON_5,
        BUTTON_6,
        BUTTON_7,
        BUTTON_8,
        LAST = BUTTON_8,
        LEFT = BUTTON_1,
        RIGHT = BUTTON_2,
        MIDDLE = BUTTON_3
    };

    int32_t MapMouseButtonToInt(MouseButton button);
    MouseButton MapIntToMouseButton(int32_t button);
}

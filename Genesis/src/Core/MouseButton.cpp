#include "Precompiled.h"
#include "Core/MouseButton.h"

namespace Genesis
{
    int32_t MapMouseButtonToInt(MouseButton button)
    {
        if (button == MouseButton::BUTTON_1) return GLFW_MOUSE_BUTTON_1;
        if (button == MouseButton::BUTTON_2) return GLFW_MOUSE_BUTTON_2;
        if (button == MouseButton::BUTTON_3) return GLFW_MOUSE_BUTTON_3;
        if (button == MouseButton::BUTTON_4) return GLFW_MOUSE_BUTTON_4;
        if (button == MouseButton::BUTTON_5) return GLFW_MOUSE_BUTTON_5;
        if (button == MouseButton::BUTTON_6) return GLFW_MOUSE_BUTTON_6;
        if (button == MouseButton::BUTTON_7) return GLFW_MOUSE_BUTTON_7;
        return GLFW_MOUSE_BUTTON_8;
    }

    MouseButton MapIntToMouseButton(int32_t button)
    {
        if (button == GLFW_MOUSE_BUTTON_1) return MouseButton::BUTTON_1;
        if (button == GLFW_MOUSE_BUTTON_2) return MouseButton::BUTTON_2;
        if (button == GLFW_MOUSE_BUTTON_3) return MouseButton::BUTTON_3;
        if (button == GLFW_MOUSE_BUTTON_4) return MouseButton::BUTTON_4;
        if (button == GLFW_MOUSE_BUTTON_5) return MouseButton::BUTTON_5;
        if (button == GLFW_MOUSE_BUTTON_6) return MouseButton::BUTTON_6;
        if (button == GLFW_MOUSE_BUTTON_7) return MouseButton::BUTTON_7;
        return MouseButton::BUTTON_8;
    }
}

#pragma once

#include "Key.h"
#include "MouseButton.h"

#include <glm/glm.hpp>

namespace Genesis
{
    class Input {
    public:
        static bool IsKeyPressed(Key key);
        static bool IsMouseButtonPressed(MouseButton button);
        static glm::ivec2 GetMousePosition();
    };
}

#include "Precompiled.h"
#include "Core/Input.h"

#include "Core/Application.h"

namespace Genesis
{
    bool Input::IsKeyPressed(Key key)
    {
        return glfwGetKey(
            static_cast<GLFWwindow*>(Application::GetWindow()->getInternalPointer()), 
            MapKeyToInt(key)
        );
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        return glfwGetMouseButton(
            static_cast<GLFWwindow*>(Application::GetWindow()->getInternalPointer()), 
            MapMouseButtonToInt(button)
        );
    }

    glm::ivec2 Input::GetMousePosition()
    {
        double xpos, ypos;
        glfwGetCursorPos(
            static_cast<GLFWwindow*>(Application::GetWindow()->getInternalPointer()),
            &xpos,
            &ypos
        );
        return { xpos, ypos };
    }
}

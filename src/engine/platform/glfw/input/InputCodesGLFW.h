#pragma once

#include "core/input/InputCodes.h"

namespace Gas {

#define GAS_GLFW_KEY_MAP \
    X(A, GLFW_KEY_A) \
    X(D, GLFW_KEY_D) \
    X(W, GLFW_KEY_W) \
    X(S, GLFW_KEY_S) \
    X(Space, GLFW_KEY_SPACE)

#define GAS_GLFW_MOUSE_BUTTON_MAP \
    X(Left, GLFW_MOUSE_BUTTON_LEFT) \
    X(Middle, GLFW_MOUSE_BUTTON_MIDDLE) \
    X(Right, GLFW_MOUSE_BUTTON_RIGHT)

    namespace GLFW {

        Key toKey(int glfwKey);

        MouseButton toMouseButton(int glfwMouseButton);

        Action toAction(int glfwAction);

    }

}
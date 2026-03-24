#pragma once

#include "InputCodes.h"

namespace Gas {

    class InputBackend
    {
    public:
        static void pushKeyEvent(Key key, Action action);
        static void pushMousePosEvent(float xPos, float yPos);
        static void pushMouseButtonEvent(MouseButton button, Action action);
        static void pushMouseScrollEvent(float xOffset, float yOffset);
    };

}
#pragma once

#include <array>

#include "InputCodes.h"
#include "core/Window.h"

namespace Gas {

    class MouseListener
    {
    public:
        static void init();
        static void update();

        static bool isDragging();

        static bool isMouseButtonDown(MouseButton button);
        static bool isMouseButtonPressed(MouseButton button);
        static bool isMouseButtonReleased(MouseButton button);
        
        static float getX();
        static float getY();
        static float getDx();
        static float getDy();

        static float getScrollX();
        static float getScrollY();

    private:
        // Maybe eventually pass native Window reference to these functions for multiple windows
        static void s_handleMousePosEvent(float xPos, float yPos);
        static void s_handleMouseButtonEvent(MouseButton button, Action action);
        static void s_handleMouseScrollEvent(float xOffset, float yOffset);

        friend class InputBackend;
    };

}
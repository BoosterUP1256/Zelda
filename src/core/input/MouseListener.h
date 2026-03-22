#pragma once

#include <array>

#include "KeyCodes.h"

namespace Gas {

    class MouseListener
    {
    public:
        static void init();
        static void update();

        static void handleMouseButtonEvent();
        static void handleMouseScrollEvent();
        
        static float getX();
        static float getY();
        static float getDx();
        static float getDy();

        static float getScrollX();
        static float getScrollY();

        static bool isDragging();

        static bool mouseButtonDown(MouseButton button);

    private:
        static float s_scrollX;
        static float s_scrollY;
        static float s_xPos;
        static float s_yPos;
        static float s_lastY;
        static float s_lastX;
        static std::array<bool, 3> s_mouseButtonPressed;
        static bool s_isDragging;
    };

}
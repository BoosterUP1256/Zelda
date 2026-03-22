#include "core/input/MouseListener.h"

namespace Gas {

    void MouseListener::init()
    {
        s_scrollX = 0.0f;
        s_scrollY = 0.0f;
        s_xPos    = 0.0f;
        s_yPos    = 0.0f;
        s_lastX   = 0.0f;
        s_lastY   = 0.0f;
    }

    void MouseListener::update()
    {
        s_scrollX = 0.0f;
        s_scrollY = 0.0f;
        s_lastX   = s_xPos;
        s_lastY   = s_yPos;
    }

}
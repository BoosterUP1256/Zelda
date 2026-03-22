#include "InputBackend.h"
#include "KeyListener.h"
#include "MouseListener.h"

namespace Gas {

    void InputBackend::pushKeyEvent(Key key, Action action)
    {
        // Later will push to event queue
        KeyListener::s_handleKeyEvent(key, action);
    }

    void InputBackend::pushMousePosEvent(float xPos, float yPos)
    {
        MouseListener::s_handleMousePosEvent(xPos, yPos);
    }

    void InputBackend::pushMouseButtonEvent(MouseButton button, Action action)
    {
        MouseListener::s_handleMouseButtonEvent(button, action);
    }

    void InputBackend::pushMouseScrollEvent(float xOffset, float yOffset)
    {
        MouseListener::s_handleMouseScrollEvent(xOffset, yOffset);
    }

}

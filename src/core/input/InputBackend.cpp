#include "InputBackend.h"
#include "KeyListener.h"

namespace Gas {

    void InputBackend::pushKeyEvent(Key key, KeyAction action)
    {
        // Later will push to event queue
        KeyListener::s_handleKeyEvent(key, action);
    }

}

#pragma once

#include "KeyCodes.h"

namespace Gas {

    class KeyListener
    {
    public:
        static void init();
        static void update();

        static bool isKeyDown(Key key);
        static bool isKeyPressed(Key key);
        static bool isKeyReleased(Key key);
    
    private:
        // Maybe eventually pass native Window reference to this function for multiple windows
        static void s_handleKeyEvent(Key key, Action action);

        friend class InputBackend;
    };

}
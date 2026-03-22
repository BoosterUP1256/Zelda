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
        static void s_handleKeyEvent(Key key, KeyAction action);

        friend class InputBackend;
    };

}
#pragma once

#include "KeyCodes.h"

namespace Gas {

    class InputBackend
    {
    public:
        static void pushKeyEvent(Key key, KeyAction action);
    };

}
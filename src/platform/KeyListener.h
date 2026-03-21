#pragma once

#include <array>

#include "KeyCodes.h"

namespace Gas {

    class KeyListener
    {
    public:
        static void init();
        static void update();

        static void handleKeyEvent(int key, int action);

        static bool isKeyDown(Key key);
        static bool isKeyPressed(Key key);
        static bool isKeyReleased(Key key);

    private:
        static void s_initKeyMap();

        static std::array<bool, static_cast<int>(Key::Count)> s_currentKeysDown;
        static std::array<bool, static_cast<int>(Key::Count)> s_previousKeysDown;
    };

}
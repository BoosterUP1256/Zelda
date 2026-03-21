#pragma once

#include <array>

#include "KeyCodes.h"

class Window;

namespace Gas {

    class KeyListener
    {
    public:
        static void init(Window* window);
        static void update();

        static bool isKeyDown(Key key);
        static bool isKeyPressed(Key key);
        static bool isKeyReleased(Key key);

    private:
        static void s_initKeyMap();
        static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static std::array<bool, static_cast<int>(Key::Count)> s_currentKeysDown;
        static std::array<bool, static_cast<int>(Key::Count)> s_previousKeysDown;
    };

}
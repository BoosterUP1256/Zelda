#include "core/input/KeyListener.h"
#include "KeyCodesGLFW.h"

#include <GLFW/glfw3.h>
#include <array>

namespace Gas {

    static std::array<bool, static_cast<int>(Key::Count)> s_currentKeysDown  {};
    static std::array<bool, static_cast<int>(Key::Count)> s_previousKeysDown {};

    void KeyListener::s_handleKeyEvent(Key key, Action action)
    {
        int index = static_cast<int>(key);

        if (action == Action::Press || action == Action::Repeat)
            s_currentKeysDown[index] = true;
        else if (action == Action::Release)
            s_currentKeysDown[index] = false;
    }

    void KeyListener::init()
    {
        // TODO: consider removing if unused
    }

    void KeyListener::update()
    {
        s_previousKeysDown = s_currentKeysDown;
    }

    bool KeyListener::isKeyDown(Key key)
    {
        return s_currentKeysDown[static_cast<int>(key)];
    }

    bool KeyListener::isKeyPressed(Key key)
    {
        return s_currentKeysDown[static_cast<int>(key)] && !s_previousKeysDown[static_cast<int>(key)];
    }

    bool KeyListener::isKeyReleased(Key key)
    {
        return !s_currentKeysDown[static_cast<int>(key)] && s_previousKeysDown[static_cast<int>(key)];
    }

}
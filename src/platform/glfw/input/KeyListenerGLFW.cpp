#include "core/input/KeyListener.h"
#include "KeyCodesGLFW.h"

#include <GLFW/glfw3.h>

namespace Gas {

    static std::array<Key, GLFW_KEY_LAST + 1> g_glfwKeyMap;

    std::array<bool, static_cast<int>(Key::Count)> KeyListener::s_currentKeysDown {};
    std::array<bool, static_cast<int>(Key::Count)> KeyListener::s_previousKeysDown {};

    void KeyListener::s_initKeyMap()
    {
        // initialize everything to unknown by default
        for (int i = 0; i <= GLFW_KEY_LAST; i++)
            g_glfwKeyMap[i] = Key::Unknown;

#define X(name, glfw) g_glfwKeyMap[glfw] = Key::name;
        GAS_GLFW_KEY_MAP
#undef X
    }

    void KeyListener::handleKeyEvent(int key, int action)
    {
        Key k = g_glfwKeyMap[key];
        if (k == Key::Unknown) return;

        s_currentKeysDown[static_cast<int>(k)] = (action != GLFW_RELEASE);
    }

    void KeyListener::init()
    {
        s_initKeyMap();
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
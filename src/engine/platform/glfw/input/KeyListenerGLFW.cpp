#include "core/input/KeyListener.h"
#include "InputCodesGLFW.h"

#include <array>
#include <cstdint>

namespace Gas {

    static uint64_t                                           s_currentFrame      = 0;
    static std::array<uint64_t, static_cast<int>(Key::Count)> s_lastPressedFrame  { 0 };
    static std::array<uint64_t, static_cast<int>(Key::Count)> s_lastReleasedFrame { 0 };
    static std::array<bool, static_cast<int>(Key::Count)>     s_currentKeysDown   { false };

    void KeyListener::s_handleKeyEvent(Key key, Action action)
    {
        const int index = static_cast<int>(key);

        if (action == Action::Press )
        {
            s_currentKeysDown[index] = true;
            s_lastPressedFrame[index] = s_currentFrame;
        }
        else if (action == Action::Release)
        {
            s_currentKeysDown[index] = false;
            s_lastReleasedFrame[index] = s_currentFrame;
        }
    }

    void KeyListener::init()
    {
        // TODO: consider removing if unused
    }

    void KeyListener::update()
    {
        s_currentFrame++;
    }

    bool KeyListener::isKeyDown(Key key)
    {
        return s_currentKeysDown[static_cast<int>(key)];
    }

    bool KeyListener::isKeyPressed(Key key)
    {
        return s_lastPressedFrame[static_cast<int>(key)] == s_currentFrame;
    }

    bool KeyListener::isKeyReleased(Key key)
    {
        return s_lastReleasedFrame[static_cast<int>(key)] == s_currentFrame;
    }

}

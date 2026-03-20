#include "KeyListener.h"

#include <GLFW/glfw3.h>
#include <memory>

namespace Gas {

    void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS) 
        {
            _currentKeysDown[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            _currentKeysDown[key] = false;
        }
    }

    void KeyListener::init(GLFWwindow* window)
    {
        _currentKeysDown = new bool[350];
        _previousKeysDown = new bool[350];
        glfwSetKeyCallback(window, keyCallback);
    }

    void KeyListener::shutdown()
    {
        delete[] _currentKeysDown;
        delete[] _previousKeysDown;
        _currentKeysDown = nullptr;
        _previousKeysDown = nullptr;
    }

    void KeyListener::update()
    {
        bool* temp = _previousKeysDown;
        _previousKeysDown = _currentKeysDown;
        _currentKeysDown = temp;
    }

    bool KeyListener::isKeyDown(int key)
    {
        return _currentKeysDown[key];
    }

    bool KeyListener::isKeyPressed(int key)
    {
        return _currentKeysDown[key] && !_previousKeysDown[key];
    }

    bool KeyListener::isKeyReleased(int key)
    {
        return !_currentKeysDown[key] && _previousKeysDown[key];
    }

}
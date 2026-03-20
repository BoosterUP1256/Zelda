#pragma once

struct GLFWwindow;

namespace Gas {

    class KeyListener
    {
    public:
        static void init(GLFWwindow* window);
        static void shutdown();
        static void update();

        static bool isKeyDown(int key);
        static bool isKeyPressed(int key);
        static bool isKeyReleased(int key);

    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        
        static bool* _currentKeysDown;
        static bool* _previousKeysDown;
    };

}
#include "core/Platform.h"

#include "core/renderer/renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"

namespace Gas {

    static void glfwErrorCallback(int error, const char* description)
    {
        std::cerr << "GLFW ERROR (" << error << "): " << description << "\n";
    }

    void Platform::init()
    {
        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit())
        {
            std::cerr << "Error: Failed to initialize GLFW.\n";
            exit(EXIT_FAILURE);
        }

        // Currently don't do anything consider removing in the future
        KeyListener::init();
        MouseListener::init();

        Renderer::init();
    }

    void Platform::shutdown()
    {
        glfwTerminate();
    }

}
#include "core/Window.h"

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

#include "core/input/KeyListener.h"
#include "platform/glfw/input/InputCodesGLFW.h"
#include "core/input/InputBackend.h"

namespace Gas {

    Window::Window(uint32_t width, uint32_t height, const std::string& title,
                   bool isFullscreen, bool isResizable)
        : _title(title),
          _width(width),
          _height(height),
          _isFullscreen(isFullscreen),
          _isResizable(isResizable)
    {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, _isResizable);
        glfwWindowHint(GLFW_MAXIMIZED, _isFullscreen);
    
        _nativeWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    
        if (!_nativeWindow)
        {
            std::cerr << "Error: failed to create window.\n";
            exit(EXIT_FAILURE);
        }

        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(_nativeWindow);
    
        glfwMakeContextCurrent(glfwWindow);
        glfwSwapInterval(1);    // Sets vsync (this might be set default anyway)

        // Initialize input
        glfwSetKeyCallback(glfwWindow, 
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                Key engineKey       = GLFW::toKey(key);
                Action engineAction = GLFW::toAction(action);
                if (engineKey == Key::Unknown || engineAction == Action::Unknown) return;

                InputBackend::pushKeyEvent(engineKey, engineAction);
            });
        
        glfwSetCursorPosCallback(glfwWindow, 
            [](GLFWwindow* window, double xpos, double ypos)
            {
                // NOTE: narrowing conversion
                InputBackend::pushMousePosEvent(xpos, ypos);
            });
        
        glfwSetMouseButtonCallback(glfwWindow,
            [](GLFWwindow* window, int button, int action, int mods)
            {
                MouseButton engineMouseButton = GLFW::toMouseButton(button);
                Action engineAction           = GLFW::toAction(action);
                if (engineMouseButton == MouseButton::Unknown || engineAction == Action::Unknown) return;

                InputBackend::pushMouseButtonEvent(engineMouseButton, engineAction);
            });
        
        glfwSetScrollCallback(glfwWindow,
            [](GLFWwindow* window, double xoffset, double yoffset)
            {
                // NOTE: narrowing conversion
                InputBackend::pushMouseScrollEvent(xoffset, yoffset);
            });
    
        glfwShowWindow(glfwWindow);
    }
    
    void Window::toggleFullscreen()
    {
        if (!_isFullscreen)
        {
            glfwMaximizeWindow(static_cast<GLFWwindow*>(_nativeWindow));
            _isFullscreen = true;
        }
        else
        {
            glfwRestoreWindow(static_cast<GLFWwindow*>(_nativeWindow));
            _isFullscreen = false;
        }
    }
    
    void Window::pollEvents()
    {
        glfwPollEvents();
    }
    
    void Window::swapBuffers()
    {
        glfwSwapBuffers(static_cast<GLFWwindow*>(_nativeWindow));
    }
    
    bool Window::shouldWindowClose()
    {
        return glfwWindowShouldClose(static_cast<GLFWwindow*>(_nativeWindow));
    }
    
    uint32_t Window::getWidth() const
    {
        return _width;
    }
    
    uint32_t Window::getHeight() const
    {
        return _height;
    }

}
#include "../../core/Window.h"

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

#include "../../core/input/KeyListener.h"

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
    
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(_nativeWindow));
        glfwSwapInterval(1);    // Sets vsync (this might be set default anyway)

        // Initialize input
        glfwSetKeyCallback(static_cast<GLFWwindow*>(_nativeWindow), 
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                Gas::KeyListener::handleKeyEvent(key, action);
            });
    
        glfwShowWindow(static_cast<GLFWwindow*>(_nativeWindow));
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
#include "core/Window.h"

#include <iostream>
#include <cstdlib>
#include <utility>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"
#include "platform/glfw/input/InputCodesGLFW.h"
#include "core/input/InputBackend.h"
#include "core/renderer/renderer.h"

namespace Gas {

    Window::Window(uint32_t width, uint32_t height, std::string  title,
                   bool isFullscreen, bool isResizable)
        : _title(std::move(title)),
          _width(width),
          _height(height),
          _isFullscreen(isFullscreen),
          _isResizable(isResizable)
    {
        // initialize propper openGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // is window fullscreen
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, _isResizable);
        glfwWindowHint(GLFW_MAXIMIZED, _isFullscreen);

        // create debug context
        // TODO: add ifdef for debug builds
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    
        _nativeWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    
        if (!_nativeWindow)
        {
            std::cerr << "Error: failed to create window.\n";
            exit(EXIT_FAILURE);
        }

        auto* glfwWindow = static_cast<GLFWwindow*>(_nativeWindow);
    
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

        // load openGL
        int openGLVersion = gladLoadGL(glfwGetProcAddress);

        if (openGLVersion== 0)
        {
            std::cout << "Failed to initialize OpenGL context\n";
            exit(EXIT_FAILURE);
        }

        int openGLVersionMajor = GLAD_VERSION_MAJOR(openGLVersion);
        int openGLVersionMinor = GLAD_VERSION_MINOR(openGLVersion);

        // check for version 4.6
        // might be unesecary because glfwWindowHint throws error if
        // cant find correct version
        if (openGLVersionMajor != 4 || openGLVersionMinor != 6)
        {
            std::cout << "OpenGL version: " << openGLVersionMajor << "." << openGLVersionMinor << " is unsupported.\n";
            std::cout << "Version 4.6 is required.\n";
            exit(EXIT_FAILURE);
        }

        // initialize renderer
        Renderer::init();
    
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
        Gas::KeyListener::update();
        Gas::MouseListener::update();
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
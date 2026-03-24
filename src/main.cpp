#include "core/Platform.h"
#include "core/Window.h"
#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"
#include "core/input/InputCodes.h"

#include <iostream>

#include <glad/gl.h>

int main()
{
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    while (!window.shouldWindowClose())
    {
        Gas::KeyListener::update();
        Gas::MouseListener::update();

        window.pollEvents();

        // Test keys
        if (Gas::KeyListener::isKeyDown(Gas::Key::A))
            std::cout << "A\n";
        if (Gas::KeyListener::isKeyPressed(Gas::Key::D))
            std::cout << "D\n";
        if (Gas::KeyListener::isKeyReleased(Gas::Key::W))
            std::cout << "W\n";

        // Test mouse
        // if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Left))
        //     std::cout << Gas::MouseListener::getX() << ", " << Gas::MouseListener::getY() << "\n";
        // if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Right))
        //     std::cout << Gas::MouseListener::getDx() << ", " << Gas::MouseListener::getDy() << "\n";
        if (Gas::KeyListener::isKeyDown(Gas::Key::Space))
            //std::cout << Gas::MouseListener::getScrollX() << Gas::MouseListener::getScrollY() << "\n";
            std::cout << Gas::MouseListener::isDragging() << "\n";
        
        if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Left))
            std::cout << "Left\n";
        if (Gas::MouseListener::isMouseButtonPressed(Gas::MouseButton::Middle))
            std::cout << "Middle\n";
        if (Gas::MouseListener::isMouseButtonReleased(Gas::MouseButton::Right))
            std::cout << "Right\n";

        
        // Render triangle!

        float points[] = {
             0.0f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        // vertex buffer object
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

        // vertex array object
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        // shaders
        const char* vertex_shader =
            "#version 410 core\n"
            "in vec3 vp;"
            "void main() {"
            "  gl_Position = vec4( vp, 1.0 );"
            "}";

        const char* fragment_shader =
            "#version 410 core\n"
            "out vec4 frag_colour;"
            "void main() {"
            "  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
            "}";
        
        // compile vertex shader
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);

        // compile fragment shader
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, NULL);
        glCompileShader(fs);

        // link shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, fs);
        glAttachShader(shaderProgram, vs);
        glLinkProgram(shaderProgram);

        // Draw tringle

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);


        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}
#include "core/Platform.h"
#include "core/Window.h"
#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"
#include "core/input/InputCodes.h"
#include "core/renderer/Shader.h"
#include "core/renderer/IndexBuffer.h"
#include "core/renderer/VertexBuffer.h"

#include <iostream>
#include <fstream>
#include <glad/gl.h>
#include <string>

int main()
{
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    constexpr float points[] = {
        -0.5f,  0.5f, 0.0f, // Top Left
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.5f,  0.5f, 0.0f  // Top Right
    };

    constexpr GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    // vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    // vertex buffer object
    // GLuint vbo = 0;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);
    Gas::VertexBuffer vbo(points, sizeof(points));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // index buffer object
    // GLuint ibo = 0;
    // glGenBuffers(1, &ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    Gas::IndexBuffer ibo(indices, 6);

    Gas::Shader shader("../src/res/shaders/basic.glsl");
    shader.bind();
    shader.setUniform4f("u_color", 0.2f, 0.3f, 0.8f, 1.0f);

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

        // Draw tringle

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();
        glBindVertexArray(vao);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}
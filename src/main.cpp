#include "core/Platform.h"
#include "core/Window.h"
#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"
#include "core/input/InputCodes.h"
#include "core/renderer/Shader.h"
#include "core/renderer/IndexBuffer.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/VertexArray.h"

#include <iostream>
#include <fstream>
#include <glad/gl.h>
#include <string>

#include "core/renderer/Renderer.h"
#include "core/renderer/Texture.h"
#include "core/Logger.h"

int main()
{
    GAS_TRACE("Hello World! %s", "Welcome to the game!");
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    constexpr float points[] = {
        0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,      0.0f, 1.0f    // top left
    };

    constexpr GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    Gas::VertexArray vao;

    Gas::VertexBuffer vbo(points, sizeof(points));
    Gas::VertexBufferLayout layout;

    layout.push<float>(3);
    layout.push<float>(2);
    vao.addBuffer(vbo, layout);

    Gas::IndexBuffer ibo(indices, 6);

    Gas::Shader shader("../src/res/shaders/basic.glsl");
    shader.bind();
    shader.setUniform4f("u_tint", 1.0, 0.71, 0.76, 1.0);

    const Gas::Texture texture("../src/res/textures/funny_face.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);

    while (!window.shouldWindowClose())
    {
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

        Gas::Renderer::clear();

        shader.bind();
        vao.bind();
        
        Gas::Renderer::draw(vao, ibo, shader);

        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}

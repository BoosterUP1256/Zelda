#include "platform/Platform.h"
#include "platform/Window.h"
#include "platform/KeyListener.h"
#include "platform/KeyCodes.h"

#include <iostream>

int main()
{
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    while (!window.shouldWindowClose())
    {
        Gas::KeyListener::update();
        window.pollEvents();

        if (Gas::KeyListener::isKeyDown(Gas::Key::A))
        {
            std::cout << "A\n";
        }
        else if (Gas::KeyListener::isKeyPressed(Gas::Key::D))
        {
            std::cout << "D\n";
        }
        else if (Gas::KeyListener::isKeyReleased(Gas::Key::W))
        {
            std::cout << "W\n";
        }
        
        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}
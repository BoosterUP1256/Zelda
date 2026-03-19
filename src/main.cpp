#include "platform/Platform.h"
#include "platform/Window.h"

int main()
{
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    while (!window.shouldWindowClose())
    {
        window.pollEvents();
        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}
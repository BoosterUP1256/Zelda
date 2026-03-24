#pragma once

#include <string>
#include <cstdint>

namespace Gas {

    class Window
    {
    public:
        Window(uint32_t width, uint32_t height, const std::string& title,
               bool isFullscreen = false, bool isResizable = false);

        void toggleFullscreen();

        void pollEvents();

        void swapBuffers();

        bool shouldWindowClose();

        uint32_t getWidth() const;
        uint32_t getHeight() const;

    private:
        void*       _nativeWindow;
        std::string _title;
        uint32_t    _width;
        uint32_t    _height;
        bool        _isFullscreen;
        bool        _isResizable;
    };

}
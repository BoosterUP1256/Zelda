#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace Gas {

    class Texture
    {
    public:
        explicit Texture(std::string_view path);
        ~Texture();

        void bind(uint32_t slot = 0) const;
        void unbind() const;

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;

    private:
        uint32_t    _rendererId;
        std::string _filePath;
        uint8_t*    _localBuffer;
        int         _width;
        int         _height;
        int         _bpp;
    };

}

#include "core/renderer/Texture.h"

#include <glad/gl.h>
#include <stb/stb_image.h>

namespace Gas {

    Texture::Texture(std::string_view path)
        : _rendererId(0),
          _filePath(path),
          _localBuffer(nullptr),
          _width(0),
          _height(0),
          _bpp(0)
    {
        stbi_set_flip_vertically_on_load(true);
        _localBuffer = stbi_load(_filePath.c_str(), &_width, &_height, &_bpp, 4);

        glGenTextures(1, &_rendererId);
        glBindTexture(GL_TEXTURE_2D, _rendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        // TODO: May want to keep _localBuffer on CPU in future (that's why _localBuffer field exists)
        if (_localBuffer)
            stbi_image_free(_localBuffer);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &_rendererId);
    }

    void Texture::bind(const uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

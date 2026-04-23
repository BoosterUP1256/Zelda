#include "core/renderer/IndexBuffer.h"

#include <glad/gl.h>

namespace Gas {

    IndexBuffer::IndexBuffer(const uint32_t* data, const uint32_t count)
        : _rendererId(0), _count(count)
    {
        glGenBuffers(1, &_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
        // TODO: consider unbindng here to avoid confusion?
    }

    IndexBuffer::~IndexBuffer()
    {
        if (_rendererId != 0)
            glDeleteBuffers(1, &_rendererId);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
        : _rendererId(other._rendererId), _count(other._count)
    {
        other._rendererId = 0;
        other._count = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            if (_rendererId != 0)
                glDeleteBuffers(1, &_rendererId);

            _rendererId = other._rendererId;
            _count = other._count;
            
            other._rendererId = 0;
            other._count = 0;
        }
        return *this;
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::getCount() const
    {
        return _count;
    }
}

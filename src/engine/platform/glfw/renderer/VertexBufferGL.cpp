#include "core/renderer/VertexBuffer.h"

#include <glad/gl.h>

namespace Gas {

    VertexBuffer::VertexBuffer(const void* data, const uint32_t size)
        : _rendererId(0)
    {
        glGenBuffers(1, &_rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        // TODO: consider unbindng here to avoid confusion?
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &_rendererId);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
        : _rendererId(other._rendererId)
    {
        other._rendererId = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if (this != &other)
            {
            if (_rendererId != 0)
                glDeleteBuffers(1, &_rendererId);

            _rendererId = other._rendererId;
            other._rendererId = 0;
        }
        return *this;
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}

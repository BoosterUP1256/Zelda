#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Gas {

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;

    private:
        uint32_t _rendererId;
    };

}
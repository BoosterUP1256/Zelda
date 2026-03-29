#pragma once

#include <vector>

// TODO: copy over correct definitions so this does not have to be included
#include "glad/gl.h"

namespace Gas {

    struct VertexBufferElement
    {
        uint32_t type;
        uint32_t count;
        unsigned char normalized;

        static uint32_t getSizeOfType(uint32_t type)
        {
            switch (type)
            {
                case GL_FLOAT:          return 4;
                case GL_UNSIGNED_INT:   return 4;
                case GL_UNSIGNED_BYTE:  return 1;
            }
            // TODO: assert false
            return 0;
        }
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout()
            : _stride(0) {}

        template<typename T>
        void push(uint32_t count)
        {
            static_assert(false);
        }

        const std::vector<VertexBufferElement>& getElements() const { return _elements; }
        uint32_t getStride() const { return _stride; }

    private:
        std::vector<VertexBufferElement> _elements;
        uint32_t _stride;
    };

    template<>
    inline void VertexBufferLayout::push<float>(uint32_t count)
    {
        _elements.push_back({ GL_FLOAT, count, GL_FALSE });
        // not sure how this is better than sizeof(GLfloat)
        _stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    inline void VertexBufferLayout::push<uint32_t>(uint32_t count)
    {
        _elements.push_back({ GL_UNSIGNED_INT, count, GL_TRUE });
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    inline void VertexBufferLayout::push<uint8_t>(uint32_t count)
    {
        _elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

}

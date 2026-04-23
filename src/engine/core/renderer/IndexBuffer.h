#pragma once
#include <cstdint>

namespace Gas {

    class IndexBuffer
    {
    public:
        IndexBuffer(const uint32_t* data, uint32_t count);
        ~IndexBuffer();

        // delete copy constructor and assignment
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        void bind() const;
        void unbind() const;

        [[nodiscard]] uint32_t getCount() const;

    private:
        uint32_t _rendererId;
        uint32_t _count;
    };

}

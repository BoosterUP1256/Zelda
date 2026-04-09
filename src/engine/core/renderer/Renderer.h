#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Gas {

    class Renderer
    {
    public:
        static void init();
        static void clear();

        // TODO: Make Material to pass into draw instead of just passing a shader
        static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    private:
        static void GLAPIENTRY _debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
            const GLchar* message, const void* userParam);
    };

}

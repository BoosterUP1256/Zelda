#include "core/renderer/renderer.h"

namespace Gas {

    void Renderer::init()
    {
        // TODO: Ifdef in debug mode
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(_debugMessageCallback, nullptr);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
    {
        shader.bind();
        va.bind();
        ib.bind();

        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::_debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
        const GLchar* message, const void* userParam)
    {
        std::string sourceString;
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
                sourceString = "GL_DEBUG_API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                sourceString = "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                sourceString = "GL_DEBUG_SOURCE_SHADER_COMPILER";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                sourceString = "GL_DEBUG_SOURCE_THIRD_PARTY";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                sourceString = "GL_DEBUG_SOURCE_APPLICATION";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                sourceString = "GL_DEBUG_SOURCE_OTHER";
                break;
            default:
                sourceString = "GL_DEBUG_UNKNOWN";
                break;
        }

        std::string typeString;
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
                typeString = "GL_DEBUG_TYPE_ERROR";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                typeString = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                typeString = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                typeString = "GL_DEBUG_TYPE_PORTABILITY";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                typeString = "GL_DEBUG_TYPE_PERFORMANCE";
                break;
            case GL_DEBUG_TYPE_MARKER:
                typeString = "GL_DEBUG_TYPE_MARKER";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                typeString = "GL_DEBUG_TYPE_PUSH_GROUP";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                typeString = "GL_DEBUG_TYPE_POP_GROUP";
                break;
            case GL_DEBUG_TYPE_OTHER:
                typeString = "GL_DEBUG_TYPE_OTHER";
                break;
            default:
                typeString = "GL_DEBUG_TYPE_UNKNOWN";
                break;
        }

        std::string severityString;
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
                severityString = "GL_DEBUG_SEVERITY_HIGH";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                severityString = "GL_DEBUG_SEVERITY_MEDIUM";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                severityString = "GL_DEBUG_SEVERITY_LOW";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                severityString = "GL_DEBUG_SEVERITY_NOTIFICATION";
                break;
            default:
                severityString = "GL_DEBUG_TYPE_UNKNOWN";
                break;
        }
    }
}

#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

namespace Gas {
    struct ShaderProgramSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    class Shader
    {
    public:
        Shader(std::string_view fragmentFilePath, std::string_view vertexFilePath);
        explicit Shader(std::string_view filePath);
        ~Shader();

        void bind() const;
        void unbind() const;

        // uniforms
        // this system will probably change for actual game implementation
        // TODO: Maybe method overloading to cut down on methods?
        void setUniform1i(std::string_view name, int value);
        void setUniform1f(std::string_view name, float value);
        void setUniform4f(std::string_view name, float f0, float f1, float f2, float f3);


    private:
        // TODO: put this elsewhere for other parts of engine to use
        static std::string _readFile(std::string_view filePath);
        static ShaderProgramSource _parseShader(std::string_view filePath);
        static uint32_t _compileShader(uint32_t type, std::string_view source);
        static uint32_t _createShader(std::string_view vertexShader, std::string_view fragmentShader);
        int _getUniformLocation(std::string_view name);

        uint32_t _rendererId;
        // caching system for uniforms
        std::unordered_map<std::string, int> _uniformLocationCache{};
    };

}
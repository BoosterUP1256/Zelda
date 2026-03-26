#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
public:
    explicit Shader(std::string_view);
    ~Shader();

    void bind() const;
    void unbind() const;

    // uniforms
    // this system will probably change for actual game implementation
    void setUniform4f(std::string_view name, float f0, float f1, float f2, float f3);


private:
    ShaderProgramSource _parseShader(std::string_view filePath);
    uint32_t _compileShader(uint32_t type, std::string_view source);
    uint32_t _createShader(std::string_view vertexShader, std::string_view fragmentShader);
    int _getUniformLocation(std::string_view name);

    uint32_t _rendererId;
    // caching system for uniforms
    std::string _filePath;
    std::unordered_map<std::string, int> _uniformLocationCache;
};
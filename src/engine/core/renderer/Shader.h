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
    Shader(const std::string& filePath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // uniforms
    // this system will probably change for actual game implementation
    void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);


private:
    ShaderProgramSource _parseShader(const std::string& filePath);
    uint32_t _compileShader(uint32_t type, const std::string& source);
    uint32_t _createShader(const std::string& vertexShader, const std::string& fragmentShader);
    int _getUniformLocation(const std::string& name);

    uint32_t _rendererId;
    // caching system for uniforms
    std::string _filePath;
    std::unordered_map<std::string, int> _uniformLocationCache;
};
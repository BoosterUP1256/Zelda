#include "core/renderer/Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/gl.h>

Shader::Shader(const std::string_view fragmentFilePath, const std::string_view vertexFilePath)
    : _rendererId(0)
{
    const std::string vertexSource = _readFile(vertexFilePath);
    const std::string fragmentSource = _readFile(fragmentFilePath);
    _rendererId = _createShader(vertexSource, fragmentSource);
}

Shader::Shader(const std::string_view filePath)
    : _rendererId(0)
{
    auto [vertexSource, fragmentSource] = _parseShader(filePath);
    _rendererId = _createShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(_rendererId);
}

void Shader::bind() const
{
    glUseProgram(_rendererId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string_view name, const float f0, const float f1, const float f2, const float f3)
{
    glUniform4f(_getUniformLocation(name), f0, f1, f2, f3);
}

std::string Shader::_readFile(const std::string_view filePath) {
    std::ifstream stream(filePath.data());

    if (!stream.is_open())
    {
        std::cerr << "Failed to open " << filePath.data() << std::endl;
        // TODO: figure out a way to fail gracefully
        exit(EXIT_FAILURE);
    }

    return std::string{ (std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>() };
}

ShaderProgramSource Shader::_parseShader(const std::string_view filePath)
{
    std::ifstream stream((filePath.data()));

    enum class ShaderType
    {
        None = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    auto type = ShaderType::None;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::_compileShader(const uint32_t type, const std::string_view source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.data();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //char message[length];
        const auto message = static_cast<char *>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        // ternary operator kind of hacky here
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;   // think about what I should actually return for error handling
    }

    return id;
}

uint32_t Shader::_createShader(const std::string_view vertexShader, const std::string_view fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vs = _compileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = _compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Maybe call glDetachShader as well?
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::_getUniformLocation(const std::string_view name)
{
    if (_uniformLocationCache.contains(name.data()))
        return _uniformLocationCache[name.data()];

    const int location = glGetUniformLocation(_rendererId, name.data());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

    _uniformLocationCache[name.data()] = location;

    return location;
}

// #pragma once

// #include <string>

// class Shader
// {
// public:
//     Shader(const std::string& filePath);
//     ~Shader();

//     void bind() const;
//     void unbind() const;

//     // uniforms
//     // this system will probably change for actual game implementation
//     void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);


// private:
//     uint32_t _compileShader();
//     uint32_t _createShader(const std::string& vertexShader, const std::string& fragmentShader);
//     uint32_t _getUniformLocation(const std::string& name);

//     uint32_t _rendererId;
//     std::string _filePath;
// };
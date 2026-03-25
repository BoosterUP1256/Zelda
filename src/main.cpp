#include "core/Platform.h"
#include "core/Window.h"
#include "core/input/KeyListener.h"
#include "core/input/MouseListener.h"
#include "core/input/InputCodes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include <string>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        None = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;
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
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static uint32_t compileShader(uint32_t type, const std::string& source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //char message[length];
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        // turnary operator kind of hacky here
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;   // think about what I should actully return for erro handeling
    }

    return id;
}

static uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Maybe call glDetachShader as well?
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    Gas::Platform::init();

    Gas::Window window(800, 600, "Game");

    ShaderProgramSource source = parseShader("../src/res/shaders/basic.glsl");
    std::cout << "VERTEX" << std::endl;
    std::cout << source.vertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.fragmentSource << std::endl;

    uint32_t shader = createShader(source.vertexSource, source.fragmentSource);

    while (!window.shouldWindowClose())
    {
        Gas::KeyListener::update();
        Gas::MouseListener::update();

        window.pollEvents();

        // Test keys
        if (Gas::KeyListener::isKeyDown(Gas::Key::A))
            std::cout << "A\n";
        if (Gas::KeyListener::isKeyPressed(Gas::Key::D))
            std::cout << "D\n";
        if (Gas::KeyListener::isKeyReleased(Gas::Key::W))
            std::cout << "W\n";

        // Test mouse
        // if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Left))
        //     std::cout << Gas::MouseListener::getX() << ", " << Gas::MouseListener::getY() << "\n";
        // if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Right))
        //     std::cout << Gas::MouseListener::getDx() << ", " << Gas::MouseListener::getDy() << "\n";
        if (Gas::KeyListener::isKeyDown(Gas::Key::Space))
            //std::cout << Gas::MouseListener::getScrollX() << Gas::MouseListener::getScrollY() << "\n";
            std::cout << Gas::MouseListener::isDragging() << "\n";
        
        if (Gas::MouseListener::isMouseButtonDown(Gas::MouseButton::Left))
            std::cout << "Left\n";
        if (Gas::MouseListener::isMouseButtonPressed(Gas::MouseButton::Middle))
            std::cout << "Middle\n";
        if (Gas::MouseListener::isMouseButtonReleased(Gas::MouseButton::Right))
            std::cout << "Right\n";

        
        // Render triangle!

        float points[] = {
             0.0f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        // vertex buffer object
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

        // vertex array object
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        // // shaders
        // const char* vertex_shader =
        //     "#version 410 core\n"
        //     "in vec3 vp;"
        //     "void main() {"
        //     "  gl_Position = vec4( vp, 1.0 );"
        //     "}";

        // const char* fragment_shader =
        //     "#version 410 core\n"
        //     "out vec4 frag_colour;"
        //     "void main() {"
        //     "  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
        //     "}";
        
        // // compile vertex shader
        // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vs, 1, &vertex_shader, NULL);
        // glCompileShader(vs);

        // // compile fragment shader
        // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fs, 1, &fragment_shader, NULL);
        // glCompileShader(fs);

        // // link shader program
        // GLuint shaderProgram = glCreateProgram();
        // glAttachShader(shaderProgram, fs);
        // glAttachShader(shaderProgram, vs);
        // glLinkProgram(shaderProgram);

        // Draw tringle

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);


        window.swapBuffers();
    }

    Gas::Platform::shutdown();
}
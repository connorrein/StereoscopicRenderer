#include "Shader.h"

std::string GetFileContents(const char* fileName)
{
    std::ifstream in(fileName, std::ios::binary);
    if (!in)
    {
        throw errno;
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

GLuint Shader::Id()
{
    return id;
}

Shader::Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
    std::string vertexShaderSourceStr = GetFileContents(vertexShaderFileName);
    std::string fragmentShaderSourceStr = GetFileContents(fragmentShaderFileName);

    const char* vertexShaderSource = vertexShaderSourceStr.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceStr.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(id);
}

void Shader::Delete()
{
    glDeleteProgram(id);
}

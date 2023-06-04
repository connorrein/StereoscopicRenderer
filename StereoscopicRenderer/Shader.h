#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* fileName);

class Shader
{
public:
    Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName);

    GLuint Id();

    void Activate();

    void Delete();

private:
    GLuint id;
};

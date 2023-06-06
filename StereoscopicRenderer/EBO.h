#pragma once

#include <vector>
#include <glad/glad.h>

// Element Buffer Object
class EBO
{
public:
    EBO(std::vector<GLuint>& indices);

    GLuint Id();

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

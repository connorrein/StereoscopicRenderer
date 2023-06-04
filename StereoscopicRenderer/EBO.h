#pragma once

#include <glad/glad.h>

// Element Buffer Object
class EBO
{
public:
    EBO(GLuint* vertices, GLsizeiptr size);

    GLuint Id();

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

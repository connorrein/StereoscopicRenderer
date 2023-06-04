#pragma once

#include <glad/glad.h>

// Vertex Buffer Object
class VBO
{
public:
    VBO(GLfloat* vertices, GLsizeiptr size);

    GLuint Id();

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

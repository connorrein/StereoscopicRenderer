#pragma once

#include <glad/glad.h>
#include "VBO.h"

// Vertex Array Object
class VAO
{
public:
    VAO();

    GLuint Id();

    void LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type,
        GLsizeiptr stride, void* offset);

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

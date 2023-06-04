#pragma once

#include <glad/glad.h>
#include "VBO.h"

// Vertex Array Object
class VAO
{
public:
    VAO();

    GLuint Id();

    void LinkVBO(VBO vbo, GLuint layout);

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

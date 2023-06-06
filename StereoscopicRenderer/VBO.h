#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 textureUv;
};

// Vertex Buffer Object
class VBO
{
public:
    VBO(std::vector<Vertex>& vertices);

    GLuint Id();

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
};

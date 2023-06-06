#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture
{
public:
    GLuint id;
    const char* type;
    GLuint unit;

    Texture(const char* imageFileName, const char* textureType, GLuint slot);

    void TextureUnit(Shader& shader, const char* uniform, GLuint unit);

    void Bind();

    void Unbind();

    void Delete();
};

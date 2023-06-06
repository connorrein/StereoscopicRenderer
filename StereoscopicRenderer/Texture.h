#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture
{
public:
    Texture(const char* imageFileName, GLenum textureType, GLuint slot,
        GLenum format, GLenum pixelType);

    void TextureUnit(Shader& shader, const char* uniform, GLuint unit);

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
    GLenum type;
    GLuint unit;
};

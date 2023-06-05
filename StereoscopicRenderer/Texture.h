#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture
{
public:
    Texture(const char* imageFileName, GLenum textureType, GLenum slot,
        GLenum format, GLenum pixelType);

    GLuint Id();

    GLenum Type();

    void TextureUnit(Shader& shader, const char* uniform, GLuint unit);

    void Bind();

    void Unbind();

    void Delete();

private:
    GLuint id;
    GLenum type;
};

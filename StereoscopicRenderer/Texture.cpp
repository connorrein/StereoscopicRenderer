#include "Texture.h"

Texture::Texture(const char* imageFileName, const char* textureType,
    GLuint slot)
{
    type = textureType;
    int textureWidth, textureHeight, textureChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(imageFileName, &textureWidth, &textureHeight, &textureChannels, 0);

    glGenTextures(1, &id);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Check what type of color channels the texture has and load it accordingly
    if (textureChannels == 4)
    {
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            textureWidth,
            textureHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bytes
        );
    }
    else if (textureChannels == 3)
    {
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            textureWidth,
            textureHeight,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            bytes
        );
    }
    else if (textureChannels == 1)
    {
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            textureWidth,
            textureHeight,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bytes
        );
    }
    else
    {
        throw std::invalid_argument("Automatic Texture type recognition failed");
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TextureUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint textureUni = glGetUniformLocation(shader.Id(), uniform);
    shader.Activate();
    glUniform1i(textureUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &id);
}

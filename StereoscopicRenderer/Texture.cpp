#include "Texture.h"

Texture::Texture(const char* imageFileName, GLenum textureType, GLenum slot,
    GLenum format, GLenum pixelType)
{
    type = textureType;
    int textureWidth, textureHeight, textureChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(imageFileName, &textureWidth, &textureHeight, &textureChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(type, id);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, bytes);
    glGenerateMipmap(type);

    stbi_image_free(bytes);
    glBindTexture(type, 0);
}

void Texture::TextureUnit(Shader shader, const char* uniform, GLuint unit)
{
    GLuint textureUni = glGetUniformLocation(shader.Id(), uniform);
    shader.Activate();
    glUniform1i(textureUni, unit);
}

GLuint Texture::Id()
{
    return id;
}

GLenum Texture::Type()
{
    return type;
}

void Texture::Bind()
{
    glBindTexture(type, id);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &id);
}

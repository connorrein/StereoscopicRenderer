#include "Texture.h"

Texture::Texture(const char* imageFileName, const char* textureType,
    GLuint slot, GLenum format, GLenum pixelType)
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, bytes);
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

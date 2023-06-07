#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::UpdateMatrix(float fovDeg, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(position, position + forward, up);
    proj = glm::perspective(glm::radians(fovDeg), (float)width / height, nearPlane, farPlane);

    cameraMatrix = proj * view;
}

void Camera::ApplyMatrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.Id(), uniform), 1, GL_FALSE,
        glm::value_ptr(cameraMatrix));
}


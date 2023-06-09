#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera(int width, int height, glm::vec3 position);

    void UpdateMatrix(float fovDeg, float nearPlane, float farPlane);

    void ApplyMatrix(Shader& shader, const char* uniform);

private:
    int width;
    int height;
    glm::mat4 cameraMatrix = glm::mat4(1.0f);
};

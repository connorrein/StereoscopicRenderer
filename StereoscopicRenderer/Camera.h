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

    Camera(int width, int height, glm::vec3 position);

    void UpdateMatrix(float fovDeg, float nearPlane, float farPlane);

    void Matrix(Shader& shader, const char* uniform);

    void HandleInput(GLFWwindow* window);

private:
    int width;
    int height;
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);
    float speed = 0.004f;
    float sensitivity = 100.0f;
    bool firstClick = true;
};

#pragma once

#include "Camera.h"

class StereoCamera
{
public:
    Camera leftCamera;
    Camera rightCamera;

    StereoCamera(float ipd, int width, int height, glm::vec3 position);

    void UpdateCameras();

    void HandleInput(GLFWwindow* window);

private:
    // Interpupillary distance
    float ipd;
    int width;
    int height;
    glm::vec3 position;
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float speed = 0.05f;
    float sensitivity = 100.0f;
    bool firstClick = true;
};

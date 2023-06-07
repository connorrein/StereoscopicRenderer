#include "StereoCamera.h"

StereoCamera::StereoCamera(float ipd, int width, int height,
    glm::vec3 position) :
    leftCamera(width / 2, height, position),
    rightCamera(width / 2, height, position)
{
    StereoCamera::ipd = ipd;
    StereoCamera::width = width;
    StereoCamera::height = height;
    StereoCamera::position = position;
}

void StereoCamera::UpdateCameras()
{
    glm::vec3 right = glm::cross(forward, up);

    leftCamera.forward = forward;
    rightCamera.forward = forward;

    leftCamera.up = up;
    rightCamera.up = up;

    leftCamera.position = position - (ipd / 2.0f) * right;
    rightCamera.position = position + (ipd / 2.0f) * right;

    leftCamera.UpdateMatrix(45.0f, 0.1f, 500.0f);
    rightCamera.UpdateMatrix(45.0f, 0.1f, 500.0f);
}

void StereoCamera::HandleInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * forward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position += speed * -glm::normalize(glm::cross(forward, up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position += speed * -forward;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * glm::normalize(glm::cross(forward, up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        position += speed * -up;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, width / 2.0f, height / 2.0f);
            firstClick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - height / 2.0f) / height;
        float rotY = sensitivity * (float)(mouseX - width / 2.0f) / width;

        glm::vec3 newOrientation = glm::rotate(forward, glm::radians(-rotX),
            glm::normalize(glm::cross(forward, up)));

        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f))
            <= glm::radians(85.0f))
        {
            forward = newOrientation;
        }

        forward = glm::rotate(forward, glm::radians(-rotY), up);
        glfwSetCursorPos(window, width / 2.0f, height / 2.0f);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

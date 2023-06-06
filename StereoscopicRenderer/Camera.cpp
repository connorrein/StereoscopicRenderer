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

void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.Id(), uniform), 1, GL_FALSE,
        glm::value_ptr(cameraMatrix));
}

void Camera::HandleInput(GLFWwindow* window)
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

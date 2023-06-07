#include "StereoCamera.h"
#include "Model.h"

const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 800;
// Interpupillary distance
const float IPD = 5;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stereoscopic Renderer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader shader("default.vert", "default.frag");

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightTransform = glm::mat4(1.0f);
    lightTransform = glm::translate(lightTransform, lightPos);

    shader.Activate();

    glUniform4f(glGetUniformLocation(shader.Id(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.Id(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    glEnable(GL_DEPTH_TEST);

    StereoCamera stereoCamera(IPD, WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    Model model("models/sword/scene.gltf");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        stereoCamera.HandleInput(window);
        stereoCamera.UpdateCameras();

        glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        model.Draw(shader, stereoCamera.leftCamera);

        glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        model.Draw(shader, stereoCamera.rightCamera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

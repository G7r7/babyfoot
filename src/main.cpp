#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <iostream>

#include "shader.hpp"
#include "model.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "game_object.hpp"
#include "scene.hpp"
#include "game.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char const *argv[])
{
    const char* TITLE = "Babyfoot";
    const unsigned int SCREEN_WIDTH = 960;
    const unsigned int SCREEN_HEIGHT = 540;

    // glfw init and config
    int init = glfwInit();
    if(init == GLFW_FALSE) {
        std::cout << "Failed to init the GLFW library." << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create the GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Mouse inputs
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad init : loads all OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    //Loading models
    Model donutModel((char*)"ressources/models/donut.obj");
    Shader donutShader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    GameObject donut(donutModel, donutShader, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    Model bulbModel((char*)"ressources/models/lightbulb.obj");
    Shader bulbShader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    GameObject bulb(bulbModel, bulbShader, glm::vec3(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    Model microsoftModel((char*)"ressources/models/microsoft.obj");
    Shader microsoftShader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    GameObject microsoft(microsoftModel, microsoftShader, glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    Light light;

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float fovGPU = 45.0f;
    Camera camera(cameraPos, cameraFront, cameraUp, fovGPU, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);

    Scene scene;
    scene.objects.push_back(donut);
    scene.objects.push_back(bulb);
    scene.objects.push_back(microsoft);
    scene.light = &light;
    scene.camera = &camera;

    Game game(window, scene);
    
    glEnable(GL_DEPTH_TEST);

    // render loop
    while (!glfwWindowShouldClose(window)) {

        // render color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        game.render();

        // glfw: swap buffers and poll IO events (keys, mouse, ...)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

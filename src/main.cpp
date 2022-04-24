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
#include "objects/bulb.hpp"
#include "objects/microsoft.hpp"
#include "objects/donut.hpp"

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
    Microsoft microsoft;
    Donut donut;
    Bulb bulb;

    Light light;
    Camera camera(45.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);

    Scene scene;
    scene.light = &light;
    scene.camera = &camera;
    scene.objects.push_back(donut);
    scene.objects.push_back(bulb);
    scene.objects.push_back(microsoft);

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

#include "window.hpp"
#include <iostream>
#include <glad/glad.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window() {
    const char* TITLE = "Babyfoot";
    const unsigned int SCREEN_WIDTH = 960;
    const unsigned int SCREEN_HEIGHT = 540;

    // glfw init and config
    int init = glfwInit();
    if(init == GLFW_FALSE) {
        std::cout << "Failed to init the GLFW library." << std::endl;
        perror("The following error occurred");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // glfw create window
    this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create the GLFW window." << std::endl;
        glfwTerminate();
        perror("Failed to create the GLFW window.");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Mouse inputs
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    // glad init : loads all OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        perror("Failed to initialize GLAD.");
    }

    // Disable V-Sync
    glfwSwapInterval(0);
}
    
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    
}

float Window::getTimeSeconds() {
    return glfwGetTime();
}

bool Window::shouldWindowClose() {
    return glfwWindowShouldClose(window);

}

void Window::close() {
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

void Window::pollEvents() {
    glfwPollEvents();
}
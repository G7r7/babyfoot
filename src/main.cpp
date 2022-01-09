#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <math.h>
#include <iostream>

#include "shader.hpp"
#include "models/loaded_model.hpp"
#include "models/tests/pyramid_model.hpp"
#include "models/tests/fancy_model.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const char* TITLE = "Babyfoot";
const unsigned int SCREEN_WIDTH = 960;
const unsigned int SCREEN_HEIGHT = 540;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrameTime = 0.0f; // Time of last frame

float mixLevel = 0.5f;

float fovGPU = 45.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool fisrtMouseInput = true;
float mouseLastX = SCREEN_WIDTH/2;
float mouseLastY = SCREEN_HEIGHT/2;

float yaw = -90.0f;
float pitch = 0.0f;

// Vertex shader : role -> outuput a value for gl_position
// Apos is the input variable (in) of type vec3 (3 float values)
// It is the first element (index 0) of the VAO.
// main : We need to make it a vec4
// we add a second input variable with location = 1 called aColor

// Fragment shader = pixel in OpenGL
// fragment shader defines how our output (out) of type vec 4 and name FragColor
// Because it is the only variable of output it corresponds by default to its color
// ourColor is a variable of type vec4 that is global throughout the program and not allowed to change (uniform)
// The uniform variable MUST be set before calling drawArrays() or drawElements()

int main(int argc, char const *argv[])
{
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
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback);


    // glad init : loads all OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    /* This is a pyramid model */
    Model my_FancyModel = initFancyModel();
    LoadedModel my_LoadedFancyModel(&my_FancyModel);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 fancyModelsPositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
    };

    // render loop
    while (!glfwWindowShouldClose(window)) {

        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;  

        // input
        process_input(window);
        
        glm::mat4 trans = glm::mat4(1.0f);
        
        // View matrix
        // it is used to move camera around
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // Perspective projection matrix
        // first is angle of the of the frustum
        // second is aspect ratio of frustum plane
        // third and forth are near and far plane coordinates
        glm::mat4 proj = glm::perspective(glm::radians(fovGPU), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);

        // Final transform matrix
        trans = proj * view * trans;

        // render color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);


        // render 
        my_LoadedFancyModel.setShaderFloat("mixLevel", mixLevel);
        my_LoadedFancyModel.setShaderInt("ourTexture0", 0);
        my_LoadedFancyModel.setShaderInt("ourTexture1", 1);
        my_LoadedFancyModel.setShaderInt("ourTexture2", 2);
        my_LoadedFancyModel.bind();

        for (size_t i = 0; i < 10; i++)
        {
            glm::mat4 model = trans;
            model = glm::translate(model, fancyModelsPositions[i]);
            if ((i+1)%3 == 0) {
                model = glm::rotate(model, currentFrameTime, glm::vec3(0.0, 1.0, 0.0));
            }
            my_LoadedFancyModel.setShaderMat4f("transform", model);
            my_LoadedFancyModel.draw();
        }

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

void process_input(GLFWwindow* window) {
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // Texture Mixing
    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS && mixLevel < 1)
        mixLevel += 0.005;
    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS && mixLevel > 0)
        mixLevel -= 0.005;
    // Camera translation
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        fovGPU += 0.05;
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        fovGPU -= 0.05;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (fisrtMouseInput) // initially set to true
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        fisrtMouseInput = false;
    }

    float xOffset = xpos - mouseLastX;
    float yOffset = mouseLastY - ypos; // reversed since y-coordinates range from bottom to top
    mouseLastX = xpos;
    mouseLastY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw   += xOffset;
    pitch += yOffset;  

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    // yaw transformation
    direction.x = cos(glm::radians(yaw)); // Note that we convert the angle to radians first
    direction.z = sin(glm::radians(yaw));
    // pitch transformation
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fovGPU -= (float)yoffset;
    if (fovGPU < 1.0f)
        fovGPU = 1.0f;
    if (fovGPU > 45.0f)
        fovGPU = 45.0f; 
}

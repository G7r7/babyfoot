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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const char* TITLE = "Babyfoot";
const unsigned int SCREEN_WIDTH = 960;
const unsigned int SCREEN_HEIGHT = 540;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrameTime = 0.0f; // Time of last frame

Light light;
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

    //Loading models
    Model donut((char*)"ressources/models/donut.obj");
    Shader donutShader((char*)"ressources/shaders/vertexShaderMatrix.vs", (char*)"ressources/shaders/fragmentShaderTextureMultiple.fs");

    Model bulb((char*)"ressources/models/lightbulb.obj");
    Shader bulbShader((char*)"ressources/shaders/vertexShaderMatrix.vs", (char*)"ressources/shaders/fragmentShaderTextureMultiple.fs");

    Model microsoft((char*)"ressources/models/microsoft.obj");
    Shader microsoftShader((char*)"ressources/shaders/vertexShaderMatrix.vs", (char*)"ressources/shaders/fragmentShaderTextureMultiple.fs");

    glEnable(GL_DEPTH_TEST);

    glm::vec3 fancyModelsPositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, 10.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
    };

    glm::vec3 pyramidModelsPositions[] = {
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
    };

    glm::vec3 lightColor(1.0f, 0.8f, 0.7f);

    // render loop
    while (!glfwWindowShouldClose(window)) {

        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;  

        // input
        process_input(window);

        // Perspective projection matrix
        // first is angle of the of the frustum
        // second is aspect ratio of frustum plane
        // third and forth are near and far plane coordinates
        glm::mat4 proj = glm::perspective(glm::radians(fovGPU), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);
        
        // View matrix
        // it is used to move camera around
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // render color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);



        glm::vec3 LightSourceModelPosition = 
            glm::vec3(-4.0f,  3.0f, -2.5f*currentFrameTime/10); 

        light.position = LightSourceModelPosition;

        donutShader.use();
        donutShader.setUniform("light", &light);
        donutShader.setMat4f("projection", proj);
        donutShader.setMat4f("view", view);
        donutShader.setVec3f("cameraPos", cameraPos);

        for (auto position : pyramidModelsPositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, -currentFrameTime/5, glm::vec3(0.0, 1.0, 0.0));
            donutShader.setMat4f("model", model);
            donut.Draw(donutShader);
        }

        bulbShader.use();
        bulbShader.setBool("lightSource", true);
        bulbShader.setUniform("light", &light);
        bulbShader.setMat4f("projection", proj);
        bulbShader.setMat4f("view", view);
        bulbShader.setVec3f("cameraPos", cameraPos);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, LightSourceModelPosition);
        bulbShader.setMat4f("model", model);
        bulb.Draw(bulbShader);

        microsoftShader.use();
        microsoftShader.setUniform("light", &light);
        microsoftShader.setMat4f("projection", proj);
        microsoftShader.setMat4f("view", view);
        microsoftShader.setVec3f("cameraPos", cameraPos);
        for (auto position : fancyModelsPositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, currentFrameTime/5, glm::vec3(0.0, 1.0, 0.0));
            microsoftShader.setMat4f("model", model);
            microsoft.Draw(microsoftShader);
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
    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS && light.strength < 1)
        light.strength += 0.0005;
    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS && light.strength > 0)
        light.strength -= 0.0005;
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

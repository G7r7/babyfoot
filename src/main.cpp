#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"

#include <math.h>
#include <iostream>

#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

const char* TITLE = "Babyfoot";
const unsigned int SCREEN_WIDTH = 960;
const unsigned int SCREEN_HEIGHT = 540;

float mixLevel = 0.5f;

float fovGPU = 45.0f;

float cameraOffsetX = 0.0f;
float cameraOffsetY = 0.0f;
float cameraOffsetZ = 0.0f;

float cameraRotationX = 0.0f;
float cameraRotationY = 0.0f;


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

    // glad init : loads all OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    Shader myShaderProgram("../src/shaders/vertexShaderMatrix.vs", "../src/shaders/fragmentShaderTextureMultiple.fs");

    // set up vertex data
    float vertices[] = {
        // positions          // colors            // texture coords
        -1.0f,  0.0f,   1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,      // top left
         1.0f,  0.0f,   1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,      // bottom left
        -1.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,      // center
         1.0f,  0.0f,  -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,      // top right
         0.0f, 1.62f,   0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,      // center
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 4,
        0, 2, 4,
        2, 3, 4,
        1, 3, 4,
    };

    // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // SETTING UP THE INPUT VARIABLES IN THE VERTEX SHADER CODE
    // for index 0 of the VAO corresponds to currently bound VBO
    // 3 corresponds to the number of elements we are reading from the buffer
    // GL_FLOAT : We're specifying the type of the data we are reading
    // GL_FALSE : not important
    // 3 * sizeof(float) : Then we specify the size of each of the element (ex: 3 floats for a vertice)  
    
    // bind the Vertex Array Object, then bind and set vertex buffer(s), and then configure attribute(s)
    glBindVertexArray(VAO);
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colors : last parameter is the byte offset in the array to skip the positions to get to the colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture:
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // TEXTURES

    // Setting up border color for GL_CLAMP_TO_BORDER option
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

    // Setting texture filtering : GL_NEAREST, GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setting texture mignification and magnification filtering : 
    // GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Loading the texture file
    int width, height, nrChannels, width2, height2, nrChannels2, width3, height3, nrChannels3;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../src/textures/verre-sur-mesure-granite.jpg", &width, &height, &nrChannels, 0); 
    unsigned char *data2 = stbi_load("../src/textures/rl.png", &width2, &height2, &nrChannels2, 0); 
    unsigned char *data3 = stbi_load("../src/textures/rl2.jpg", &width3, &height3, &nrChannels3, 0); 

    // Generating the texture
    // 2 is the number of textures we generate
    // store the generated textures in an unsigned int array
    unsigned int textures[3];
    glGenTextures(3, textures);  


    // We bind the generated texture to the current context
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
    glGenerateMipmap(GL_TEXTURE_2D);

    // we can free the loaded image
    stbi_image_free(data);
    stbi_image_free(data2);
    stbi_image_free(data3);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 pyramidPositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // render loop
    while (!glfwWindowShouldClose(window)) {
        _sleep(10);

        // input
        process_input(window);
        
        glm::mat4 trans = glm::mat4(1.0f);
        // Translation matrix
        // glm::vec3 vec(offsetX, offsetY, 0.0f);
        // trans = glm::translate(trans, vec);
        // // Rotation matrix
        // trans = glm::rotate(trans, glm::radians(rotationX), glm::vec3(1.0, 0.0, 0.0));
        // trans = glm::rotate(trans, glm::radians(rotationY), glm::vec3(0.0, 1.0, 0.0));
        // // Scaling matrix
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        
        // View matrix
        // it is used to move camera around
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::rotate(view, glm::radians(cameraRotationX), glm::vec3(1.0, 0.0, 0.0));
        view = glm::rotate(view, glm::radians(cameraRotationY), glm::vec3(0.0, 1.0, 0.0));
        view = glm::translate(view, glm::vec3(-cameraOffsetX, -cameraOffsetY, -cameraOffsetZ));

        // Orthographic projection matrix
        // 0 and 800 are the left and right coordinates of the frustum
        // 0 and 600 are the bottom and top coordinates of the frustum
        // 0.1 and 100 are the front and back coordinates of the frustum
        // glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, 0.1f, 100.0f);

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
        myShaderProgram.use();
        myShaderProgram.setFloat("mixLevel", mixLevel);
        myShaderProgram.setInt("ourTexture0", 0);
        myShaderProgram.setInt("ourTexture1", 1);
        myShaderProgram.setInt("ourTexture2", 2);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        for (size_t i = 0; i < 10; i++)
        {
            glm::mat4 model = trans;
            model = glm::translate(model, pyramidPositions[i]);
            if ((i+1)%3 == 0) {
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 1.0, 0.0));
            }
            myShaderProgram.setMat4f("transform", model);
            glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_INT, 0);
        }

        // glfw: swap buffers and poll IO events (keys, mouse, ...)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraOffsetX += 0.01;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraOffsetX -= 0.01;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraOffsetY += 0.01;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraOffsetY -= 0.01;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraOffsetZ += 0.01;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraOffsetZ -= 0.01;
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        fovGPU += 0.05;
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        fovGPU -= 0.05;
    
    double X, Y = 0;
    int windowWidth, windowHeight = 0;
    glfwGetCursorPos(window, &X, &Y);
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    cameraRotationX = (Y - windowHeight / 2) * 0.3f;
    cameraRotationY = (X - windowWidth / 2) * 0.3f;
}
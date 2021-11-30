#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <math.h>
#include <iostream>

#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

const char* TITLE = "Babyfoot";
const unsigned int SCREEN_WIDTH = 960;
const unsigned int SCREEN_HEIGHT = 540;

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

    Shader myShaderProgram("../src/shaders/vertexShader.vs", "../src/shaders/fragmentShader.fs");
    Shader myShaderProgram2("../src/shaders/vertexShader.vs", "../src/shaders/fragmentShaderTexture.fs");

    // set up vertex data
    float vertices[] = {
        // positions          // colors            // texture coords
        -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,      // top left
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,      // bottom left
         0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,      // center
         0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,      // top right
         0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,      // bottom right
         0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,      // center
    };

    // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    unsigned int VBO, VAO, VBO2, VAO2;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

    glBindVertexArray(VAO2);
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(24 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // colors : last parameter is the byte offset in the array to skip the positions to get to the colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(27 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture:
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(30 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // we unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // TEXTURES

    // Texture wrapping options : GL_REPEAT (default), GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

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
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../src/textures/verre-sur-mesure-granite.jpg", &width, &height, &nrChannels, 0); 

    // Generating the texture
    // 1 is the number of textures we generate
    // store the generated textures in an unsigned int array
    unsigned int texture;
    glGenTextures(1, &texture);  

    // We bind the generated texture to the current context
    glBindTexture(GL_TEXTURE_2D, texture);

    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // we can free the loaded image
    stbi_image_free(data);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // render color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double time = glfwGetTime();
        double mod = 2.0f;
        float offset = sin(time);

        // render triangle
        myShaderProgram.use();
        myShaderProgram.setFloat("offsetX", offset);
        glBindVertexArray(VAO); // bind
        glDrawArrays(GL_TRIANGLES, 0, 3);
        myShaderProgram2.use();
        myShaderProgram2.setFloat("offsetY", offset);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO2); // bind
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0); // unbind

        // glfw: swap buffers and poll IO events (keys, mouse, ...)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
}
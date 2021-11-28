#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <iostream>

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
const char* vertexShaderSource = R"HERE(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 ourColor;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);    
        ourColor = aColor;
    }
)HERE";

// fragment = pixel in OpenGL
// fragment shader defines how our output (out) of type vec 4 and name FragColor
// Because it is the only variable of output it corresponds by default to its color
// ourColor is a variable of type vec4 that is global throughout the program and not allowed to change (uniform)
// The uniform variable MUST be set before calling drawArrays() or drawElements()
const char* fragmentShaderSource = R"HERE(
    #version 330 core

    in vec3 ourColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(ourColor, 1.0f);    
    }
)HERE";

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

    // shader program : build and compile
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data
    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  // bottom left
         0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
         0.0f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f,  // top
    };

    // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object, then bind and set vertex buffer(s), and then configure attribute(s)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // to the current bound buffer
    // We put the data in the VBO, GL_STATIC_DRAW flag influence how the data will be layed out in memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // SETTING UP THE INPUT VARIABLES IN THE VERTEX SHADER CODE
    // for index 0 of the VAO corresponds to currently bound VBO
    // 3 corresponds to the number of elements we are reading from the buffer
    // GL_FLOAT : We're specifying the type of the data we are reading
    // GL_FALSE : not important
    // 3 * sizeof(float) : Then we specify the size of each of the element (ex: 3 floats for a vertice)  
    
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colors : last parameter is the byte offset in the array to skip the positions to get to the colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // we unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // render color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Setting uniform variables
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue);
        glUniform4f(vertexColorLocation, 1-greenValue, greenValue, 0.1f, 1.0f);

        // render triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // bind
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
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char const *argv[])
{
    int init = glfwInit();
    std::cout << "J'ai init ! Ca a fait ca : " << init;
    return 0;
}

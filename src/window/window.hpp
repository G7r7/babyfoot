#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct Window {
    Window();
    GLFWwindow* window;
    float getTimeSeconds();
    bool shouldWindowClose();
    void close();
    void swapBuffers();
    void pollEvents();
};

#endif
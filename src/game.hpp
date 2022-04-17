#ifndef GAME_H
#define GAME_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "scene.hpp"
#include "input_handler.hpp"

class InputHandler;

class Game
{
    public:
    Game(GLFWwindow* window, Scene& scene);
    void render();
    void process_inputs();
    GLFWwindow* window;
    Scene scene;
    InputHandler* inputHandler;
    float deltaTime;
    float lastFrameTime;
};


#endif
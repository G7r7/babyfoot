#ifndef GAME_H
#define GAME_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "engine/scene.hpp"
#include "input_handler.hpp"
#include "engine/physics/physics_processor.hpp"

class InputHandler;

class Game
{
    public:
    Game(GLFWwindow* window, Scene&& scene);
    void render();
    void process_inputs();
    GLFWwindow* window;
    Scene scene;
    InputHandler* inputHandler;
    PhysicsProcessor physicsProcessor;
    float deltaTime;
    float lastFrameTime;
};


#endif
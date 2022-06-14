#include "game.hpp"

Game::Game(GLFWwindow* window, Scene&& scene)
: window{window}, scene{std::move(scene)}, deltaTime{0.0f}, lastFrameTime{0.0f}, inputHandler{new InputHandler(this)}
{
    glfwSetWindowUserPointer(this->window, this); //We bind the Game Class instance to the window, to access it later
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
        Game* game = (Game*)glfwGetWindowUserPointer(window);
        game->scene.camera.aspect_ration = (float)width/(float)height;
    });
}

void Game::render() {
    float currentFrameTime = glfwGetTime();
    this->deltaTime = currentFrameTime - this->lastFrameTime;
    this->lastFrameTime = currentFrameTime;
    this->process_inputs();
    this->physicsProcessor.process(&scene, deltaTime);
    this->scene.render();
}

void Game::process_inputs() {
    this->inputHandler->process_inputs();
}
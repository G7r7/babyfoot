#include "game.hpp"

Game::Game(GLFWwindow* window, Scene& scene)
: window{window}, scene{std::move(scene)}, deltaTime{0.0f}, lastFrameTime{0.0f}, inputHandler{new InputHandler(this)}
{}

void Game::render() {
    float currentFrameTime = glfwGetTime();
    this->deltaTime = currentFrameTime - this->lastFrameTime;
    this->lastFrameTime = currentFrameTime;
    this->process_inputs();
    this->scene.render();
}

void Game::process_inputs() {
    this->inputHandler->process_inputs();
}
#include "engine.hpp"

Engine::Engine(Window* window): window{window}{};

void Engine::process(Game &game) {
    float deltaTime = 0.f;
    float lastFrameTime = 0.f;
    float currentFrameTime = this->window->getTimeSeconds();

    this->inputHandler.bind_input_callbacks(this->window, &game);

    while (!window->shouldWindowClose())
    {
        currentFrameTime = this->window->getTimeSeconds();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        this->inputHandler.process_inputs(this->window, &game, deltaTime);
        this->physicsProcessor.process(&game.scene, deltaTime);
        this->renderer.render(&game.scene);

        // swap buffers and poll IO events (keys, mouse, ...)
        this->window->swapBuffers();
        this->window->pollEvents();
    }
    
    window->close();
}
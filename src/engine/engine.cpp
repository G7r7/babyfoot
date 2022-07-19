#include "engine.hpp"
#include <chrono>
#include <thread>


Engine::Engine(Window* window): window{window}{};

void Engine::process(Game &game) {
    // In-game time
    float ticksPerSecond = 100;
    float tickDeltaTime = 1/ticksPerSecond;

    // System time
    float deltaTime;
    float currentFrameTime;
    float lastFrameTime = 0.f;
    
    this->inputHandler.bind_input_callbacks(this->window, &game);

    while (!window->shouldWindowClose())
    {

        this->inputHandler.process_inputs(this->window, &game, tickDeltaTime);
        this->physicsProcessor.process(&game.scene, tickDeltaTime);
        this->renderer.render(&game.scene);

        // swap buffers and poll IO events (keys, mouse, ...)
        this->window->swapBuffers();
        this->window->pollEvents();

        currentFrameTime = this->window->getTimeSeconds();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // We wait to sync the game time to the system time
        if(deltaTime < tickDeltaTime) {
            int millisecondsEarly = std::round((tickDeltaTime - deltaTime)*1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsEarly));
            deltaTime += millisecondsEarly/1000;
        }

        if(currentFrameTime - std::floor(currentFrameTime) > 0.99) {
            std::cout << "Framerate : " << glm::round(1/deltaTime) << " fps" << std::endl;
            std::cout << "Temps réel : " << glm::round(tickDeltaTime/deltaTime*100) << "%" << std::endl;
        }

        
        
    }
    
    window->close();
}
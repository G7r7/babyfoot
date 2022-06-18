#include "physics/physics_processor.hpp"
#include "render/renderer.hpp"
#include "game.hpp"
#include "inputs/input_handler.hpp"
#include "../window/window.hpp"

struct Engine {
    Engine(Window* window);
    Window* window;
    PhysicsProcessor physicsProcessor;
    Renderer renderer;
    InputHandler inputHandler;
    void process(Game &game);
};
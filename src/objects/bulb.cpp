#include "bulb.hpp"

GameObject doABulb() {
    Model model((char*)"ressources/models/lightbulb.obj");
    Shader shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    return GameObject(model, shader);
}

Bulb::Bulb() : GameObject(doABulb()) {}
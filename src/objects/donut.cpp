#include "donut.hpp"

GameObject doADonut() {
    Model model((char*)"ressources/models/donut.obj");
    Shader shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    return GameObject(model, shader);
}

Donut::Donut() : GameObject(doADonut()) {}
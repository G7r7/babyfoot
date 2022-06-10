#include "bulb.hpp"

Bulb::Bulb() : GameObject([]{
    return GameObject(
        Model((char*)"ressources/models/lightbulb/lightbulb.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
}()) {}
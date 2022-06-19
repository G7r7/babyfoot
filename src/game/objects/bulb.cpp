#include "bulb.hpp"

Bulb::Bulb() : GameObject([]{
    GameObject bulb(
        Model((char*)"ressources/models/lightbulb/lightbulb.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
    bulb.hitbox = Model((char*)"ressources/models/lightbulb/hitbox.obj");
    return bulb;
}()) {}
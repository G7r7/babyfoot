#include "donut.hpp"

Donut::Donut() : GameObject([]{
    return GameObject(
        Model((char*)"ressources/models/donut/donut.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
}()){}
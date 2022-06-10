#include "ball.hpp"

Ball::Ball() : GameObject([]{
    return GameObject(
        Model((char*)"ressources/models/ball.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
}()){}
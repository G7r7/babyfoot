#include "ball.hpp"


GameObject doABall() {
    Model model((char*)"ressources/models/ball.obj");
    Shader shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    return GameObject(model, shader);
}

Ball::Ball() : GameObject(doABall()) {}
#include "ball.hpp"

Ball::Ball() : GameObject([]{
    GameObject ball(
        Model((char*)"ressources/models/ball/ball.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
    ball.hitbox = Model((char*)"ressources/models/ball/hitbox.obj");
    return ball;
}()){}
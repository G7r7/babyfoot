#include "ball.hpp"

Ball::Ball() : GameObject(
    Model("ressources/models/ball/ball.obj"),
    Shader("ressources/shaders/vertex.vs", "ressources/shaders/fragment.fs"),
    Model("ressources/models/ball/hitbox.obj")
){}
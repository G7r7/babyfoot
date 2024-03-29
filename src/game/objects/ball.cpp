#include "ball.hpp"

Ball::Ball() : GameObject(
    Model("ressources/models/ball/ball.obj"),
    Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl"),
    Model("ressources/models/ball/hitbox.obj")
){}
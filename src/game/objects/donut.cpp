#include "donut.hpp"

Donut::Donut() : GameObject(
        Model("ressources/models/donut/donut.obj"),
        Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl"),
        Model("ressources/models/ball/hitbox.obj")    
){}
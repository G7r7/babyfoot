#include "donut.hpp"

Donut::Donut() : GameObject(
        Model("ressources/models/donut/donut.obj"),
        Shader("ressources/shaders/vertex.vs", "ressources/shaders/fragment.fs"),
        Model("ressources/models/ball/hitbox.obj")    
){}
#include "field.hpp"

Field::Field() : GameObject(
        Model("ressources/models/field/field.obj"),
        Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl")
){}
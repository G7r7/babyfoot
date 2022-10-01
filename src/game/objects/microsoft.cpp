#include "microsoft.hpp"

Microsoft::Microsoft() : GameObject(
    Model("ressources/models/microsoft/microsoft.obj"),
    Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl"),
    Model("ressources/models/microsoft/microsoft.obj")
){}
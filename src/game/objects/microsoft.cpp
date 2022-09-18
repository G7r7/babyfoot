#include "microsoft.hpp"

Microsoft::Microsoft() : GameObject(
    Model("ressources/models/microsoft/microsoft.obj"),
    Shader("ressources/shaders/vertex.vs", "ressources/shaders/fragment.fs"),
    Model("ressources/models/microsoft/microsoft.obj")
){}
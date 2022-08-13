#include "microsoft.hpp"

Microsoft::Microsoft() : GameObject(
    Model((char*)"ressources/models/microsoft/microsoft.obj"),
    Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs"),
    Model((char*)"ressources/models/microsoft/microsoft.obj")
){}
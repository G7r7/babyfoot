#include "microsoft.hpp"

Microsoft::Microsoft() : GameObject([]{
    GameObject microsoft(
        Model((char*)"ressources/models/microsoft/microsoft.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
    microsoft.hitbox = Model((char*)"ressources/models/microsoft/microsoft.obj");
    return microsoft;
}()){}
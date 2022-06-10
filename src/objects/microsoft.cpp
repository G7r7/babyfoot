#include "microsoft.hpp"

Microsoft::Microsoft() : GameObject([]{
    return GameObject(
        Model((char*)"ressources/models/microsoft.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
}()){}
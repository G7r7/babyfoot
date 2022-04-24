#include "microsoft.hpp"

GameObject doAMircosoft() {
    Model model((char*)"ressources/models/microsoft.obj");
    Shader shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs");
    return GameObject(model, shader);
}

Microsoft::Microsoft() : GameObject(doAMircosoft()) {}
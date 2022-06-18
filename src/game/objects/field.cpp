#include "field.hpp"

Field::Field() : GameObject([]{
    return GameObject(
        Model((char*)"ressources/models/field/field.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
}()){}
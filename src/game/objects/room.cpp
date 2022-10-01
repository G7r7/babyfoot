#include "room.hpp"

Room::Room() : GameObject(
    Model("ressources/models/room/room.obj"),
    Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl"),
    Model("ressources/models/room/room.obj")
){}
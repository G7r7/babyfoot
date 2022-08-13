#include "room.hpp"

Room::Room() : GameObject(
    Model("ressources/models/room/room.obj"),
    Shader("ressources/shaders/vertex.vs", "ressources/shaders/fragment.fs"),
    Model("ressources/models/room/room.obj")
){}
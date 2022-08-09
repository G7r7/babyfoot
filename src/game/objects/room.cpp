#include "room.hpp"

Room::Room() : GameObject([]{
    GameObject room(
        Model((char*)"ressources/models/room/room.obj"),
        Shader((char*)"ressources/shaders/vertex.vs", (char*)"ressources/shaders/fragment.fs")
    );
    room.hitbox = Model((char*)"ressources/models/room/room.obj");
    return room;
}()){}
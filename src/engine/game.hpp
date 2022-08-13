#ifndef GAME_H
#define GAME_H

#include "scene/scene.hpp"

class Game
{ // TODO: Refactor (put members in private etc.)
public:
    Game(Scene&& scene);
    Scene scene;
};


#endif
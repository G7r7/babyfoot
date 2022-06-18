#ifndef GAME_H
#define GAME_H

#include "scene/scene.hpp"

struct Game
{
    public:
    Game(Scene&& scene);
    Scene scene;
};


#endif
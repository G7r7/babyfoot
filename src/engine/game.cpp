#include "game.hpp"

Game::Game(Scene&& scene): scene{std::move(scene)}{}
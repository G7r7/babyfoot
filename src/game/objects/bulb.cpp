#include "bulb.hpp"

Bulb::Bulb() : GameObject(
	Model("ressources/models/lightbulb/lightbulb.obj"),
	Shader("ressources/shaders/vertex.vs", "ressources/shaders/fragment.fs"),
	Model("ressources/models/ball/hitbox.obj")
){}
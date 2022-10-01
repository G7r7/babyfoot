#include "bulb.hpp"

Bulb::Bulb() : GameObject(
	Model("ressources/models/lightbulb/lightbulb.obj"),
	Shader("ressources/shaders/vertex.glsl", "ressources/shaders/fragment.glsl"),
	Model("ressources/models/ball/hitbox.obj")
){}
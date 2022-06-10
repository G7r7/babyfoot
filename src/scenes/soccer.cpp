#include "soccer.hpp"
#include "../objects/ball.hpp"
#include "../objects/field.hpp"

SoccerLevel::SoccerLevel() : Scene([]{
    Ball ball;
    ball.move(glm::vec3(0, 2.0f, 0));
    Field field;
    return Scene(
        Camera(45.0f, 16.f/9.f, 0.1f, 100.0f),
        Light(),
        {
            ball,
            field
        }
    );
}()) {}


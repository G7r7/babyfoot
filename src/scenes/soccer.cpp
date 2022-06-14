#include "soccer.hpp"
#include "../objects/ball.hpp"
#include "../objects/field.hpp" 
#include "../objects/bulb.hpp" 

SoccerLevel::SoccerLevel() : Scene([]{
    Bulb bulb;
    Ball ball;
    Field field;
    return Scene(
        Camera(45.0f, 16.f/9.f, 0.1f, 100.0f),
        Light(),
        {
            bulb,
            field,
            ball,
        },
        glm::vec3(0,0.001,0)
    );
}()) {}


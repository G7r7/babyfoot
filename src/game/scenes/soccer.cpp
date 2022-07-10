#include "soccer.hpp"
#include "../objects/ball.hpp"
#include "../objects/field.hpp" 
#include "../objects/bulb.hpp" 

SoccerLevel::SoccerLevel() : Scene([]{
    Bulb bulb;
    bulb.move(glm::vec3(2.f, -1.5f, 0));
    Ball ball;
    ball.move(glm::vec3(1.f, -1.5f, 0));
    Field field;
    field.fixed = true;
    Camera camera(45.0f, 16.f/9.f, 0.1f, 100.0f);
    camera.position.y += 1.5f;
    return Scene(
        camera,
        Light(),
        {
            bulb,
            ball,
            field,
        },
        glm::vec3(0,0.2,0)
    );
}()) {}


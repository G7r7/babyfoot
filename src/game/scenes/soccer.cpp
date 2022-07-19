#include "soccer.hpp"
#include "../objects/ball.hpp"
#include "../objects/field.hpp" 
#include "../objects/bulb.hpp" 

SoccerLevel::SoccerLevel() : Scene([]{
    Ball ball;
    ball.move(glm::vec3(2.f, -1.5f, 0));
    ball.speed = glm::vec3(-0.1f, 0, 0);
    Ball ball2;
    ball2.move(glm::vec3(1.f, -1.5f, 0.02));
    ball2.speed = glm::vec3(0.1f, 0, 0);
    Ball ball3;
    ball3.move(glm::vec3(0.f, -1.5f, 0));
    ball3.speed = glm::vec3(-0.1f, 0, 0);
    Ball ball4;
    ball4.move(glm::vec3(-1.f, -1.5f, 0));
    ball4.speed = glm::vec3(-0.1f, 0, 0);
    Field field;
    field.fixed = true;
    Camera camera(45.0f, 16.f/9.f, 0.1f, 100.0f);
    camera.position.y += 1.5f;
    return Scene(
        camera,
        Light(),
        {
            ball,
            ball2,
            // ball3,
            // ball4,
            field,
        },
        glm::vec3(0,0.2,0)
    );
}()) {}


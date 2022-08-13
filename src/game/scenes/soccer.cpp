#include "soccer.hpp"
#include "../objects/ball.hpp"
#include "../objects/field.hpp" 
#include "../objects/bulb.hpp" 
#include "../objects/microsoft.hpp"
#include "../objects/room.hpp"

SoccerLevel::SoccerLevel() : Scene([]{
    Ball ball;
    ball.move(glm::vec3(-2.0f, -1.5f, 0.f));
    ball.setSpeed(glm::vec3(0.5f, 0, 0));
    Ball ball2;
    ball2.move(glm::vec3(2.0f, -1.5f, 0));
    ball2.setSpeed(glm::vec3(-0.5f, 0, 0));
    Ball ball3;
    ball3.move(glm::vec3(0, -1.5f, -2.0f));
    ball3.setSpeed(glm::vec3(0, 0, 0.5f));
    Ball ball4;
    ball4.move(glm::vec3(0, -1.5f, 2.0f));
    ball4.setSpeed(glm::vec3(0, 0, -0.5f));
    Field field;
    field.setGravitable(false);
    Room room;
    room.setGravitable(false);
    Camera camera(45.0f, 16.f/9.f, 0.1f, 100.0f);
    camera.position.y += 1.5f;
    return Scene(
        camera,
        Light(),
        {
            ball,
            ball2,
            ball3,
            ball4,
            field,
            // room,
        },
        glm::vec3(0,0.2,0)
    );
}()) {}


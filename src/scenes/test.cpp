#include "test.hpp"
#include "../objects/microsoft.hpp"
#include "../objects/donut.hpp"
#include "../objects/bulb.hpp"
#include "../objects/ball.hpp"

TestLevel::TestLevel() : Scene([]{    
    return Scene(
        Camera(45.0f, 16.f/9.f, 0.1f, 100.0f),
        Light(),
        {
            Microsoft(),
            Donut(),
            Bulb(),
            Ball(),
        },
        glm::vec3(0.1f)
    );
}()) {}


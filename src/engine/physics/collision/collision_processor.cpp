#include "collision_processor.hpp"
#include "triangle/triangle_collision.hpp"



void CollisionProcessor::process(Scene* scene) {
    // Loop over every unordered combination
    for (auto first = scene->objects.begin(); first != scene->objects.end(); ++first){
        for (auto second = first + 1; second != scene->objects.end(); ++second){
            std::cout << first->model.directory << " - vs - " << second->model.directory << std::endl;
            process(&*first, &*second);
        }
    }
}

void CollisionProcessor::process(GameObject* object1, GameObject* object2) {
    int c = 0;
    for (auto &mesh1 : object1->hitbox.meshes) // Every mesh of hitbox 1
    {
        for (auto &mesh2 : object2->hitbox.meshes) // Every mesh of hitbox 2
        {
            std::cout << mesh1.indices.size() << " <- mesh1 - mesh2 -> " << mesh2.indices.size() << std::endl;
            for (size_t i = 0; i < mesh1.indices.size(); i+=3) // Every triangle of mesh 1
            {
                glm::vec3 point11 = mesh1.vertices[i].Position + object1->position;
                glm::vec3 point12 = mesh1.vertices[i+1].Position + object1->position;
                glm::vec3 point13 = mesh1.vertices[i+2].Position + object1->position;
                for (size_t j = 0; j < mesh2.indices.size(); j+=3) // Every triangle of mesh 2
                {
                    glm::vec3 point21 = mesh2.vertices[j].Position + object2->position;
                    glm::vec3 point22 = mesh2.vertices[j+1].Position + object2->position;
                    glm::vec3 point23 = mesh2.vertices[j+2].Position + object2->position;

                    glm::vec3 intersection;
                    bool collision = checkForIntersection(point11, point12, point13, point21, point22, point23, &intersection);
                    if(collision) {
                        std::cout << "Cosllision between : " << object1->model.directory << " and " << object2->model.directory << std::endl;
                        std::cout << "Triangle 1 - point 1 : (" << point11.x << ", " << point11.y << ", " << point11.z << ")" << std::endl;
                        std::cout << "Triangle 1 - point 2 : (" << point12.x << ", " << point12.y << ", " << point12.z << ")" << std::endl;
                        std::cout << "Triangle 1 - point 3 : (" << point13.x << ", " << point13.y << ", " << point13.z << ")" << std::endl;
                        std::cout << "Triangle 2 - point 1 : (" << point21.x << ", " << point21.y << ", " << point21.z << ")" << std::endl;
                        std::cout << "Triangle 2 - point 2 : (" << point22.x << ", " << point22.y << ", " << point22.z << ")" << std::endl;
                        std::cout << "Triangle 2 - point 3 : (" << point23.x << ", " << point23.y << ", " << point23.z << ")" << std::endl;
                        std::cout << "Intersection : (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;
                        if(object1->fixed == false) {
                            object1->speed = glm::vec3(0, -0.5f,0);
                        }
                        if(object2->fixed == false) {
                            object2->speed = glm::vec3(0, -0.5f,0);

                        }
                    }
                    c++;
                }
            
            }
        }
    }
    std::cout << c << std::endl;
}

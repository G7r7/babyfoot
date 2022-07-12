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
    std::vector<glm::vec3> intersections;
    std::vector<glm::vec3> surface_normals_1;
    std::vector<glm::vec3> surface_normals_2;
    for (auto &mesh1 : object1->hitbox.meshes) // Every mesh of hitbox 1
    {
        for (auto &mesh2 : object2->hitbox.meshes) // Every mesh of hitbox 2
        {
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
                    glm::vec3 normal1;
                    glm::vec3 normal2;
                    bool collision = checkForIntersection(point11, point12, point13, point21, point22, point23,
                        &intersection, &normal1, &normal2);
                    if(collision) {
                        intersections.push_back(intersection);
                        surface_normals_1.push_back(normal1);
                        surface_normals_2.push_back(normal2);
                    }
                }
            
            }
        }
    }
    if(intersections.size() > 0) {
        glm::vec3 average_collision_point = [intersections](){
            glm::vec3 average(0.f);
            for(glm::vec3 intersection : intersections) {
                average += intersection;
            }
            return average / glm::vec3(intersections.size());
        }();

        glm::vec3 average_surface_normal_1 = [surface_normals_1](){
            glm::vec3 average(0.f);
            for(glm::vec3 normal : surface_normals_1) {
                average += normal;
            }
            return glm::normalize(average / glm::vec3(surface_normals_1.size()));
        }();

        glm::vec3 average_surface_normal_2 = [surface_normals_2](){
            glm::vec3 average(0.f);
            for(glm::vec3 normal : surface_normals_2) {
                average += normal;
            }
            return glm::normalize(average / glm::vec3(surface_normals_2.size()));
        }();
        std::cout << "Point d'impact : (" 
            << average_collision_point.x << ", " 
            << average_collision_point.y << ", "
            << average_collision_point.z << ")" << std::endl;
        std::cout << "Normale 1 : (" 
            << average_surface_normal_1.x << ", " 
            << average_surface_normal_1.y << ", "
            << average_surface_normal_1.z << ")" << std::endl;
        std::cout << "Normale 2 : (" 
            << average_surface_normal_2.x << ", " 
            << average_surface_normal_2.y << ", "
            << average_surface_normal_2.z << ")" << std::endl;
        
        if(object1->fixed == false) {
            object1->speed = glm::reflect(object1->speed, average_surface_normal_2);
        }
        if(object2->fixed == false) {
            object2->speed = glm::reflect(object2->speed, average_surface_normal_1);
        }
    }
}

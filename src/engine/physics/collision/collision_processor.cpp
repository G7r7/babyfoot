#include "collision_processor.hpp"
#include "triangle/triangle_collision.hpp"

glm::vec4 planeEquation(Vertex* v1, Vertex* v2, Vertex* v3);
float sideOfPlane(glm::vec4* p, Vertex* v);
bool sameSign(float d1, float d2, float d3);

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
                double p11[3] = { point11.x, point11.y, point11.z };

                glm::vec3 point12 = mesh1.vertices[i+1].Position + object1->position;
                double p12[3] = { point12.x, point12.y, point12.z };

                glm::vec3 point13 = mesh1.vertices[i+2].Position + object1->position;
                double p13[3] = { point13.x, point13.y, point13.z };

                for (size_t j = 0; j < mesh2.indices.size(); j+=3) // Every triangle of mesh 2
                {
                    glm::vec3 point21 = mesh2.vertices[j].Position + object2->position;
                    double p21[3] = { point21.x, point21.y, point21.z };

                    glm::vec3 point22 = mesh2.vertices[j+1].Position + object2->position;
                    double p22[3] = { point22.x, point22.y, point22.z };

                    glm::vec3 point23 = mesh2.vertices[j+2].Position + object2->position;
                    double p23[3] = { point23.x, point23.y, point23.z };

                    int coplanar = 0;
                    double source[3] = {0,0,0};
                    double target[3] = {0,0,0};
                    int collision = tri_tri_intersection_test_3d(p11, p12, p13, p21, p22, p23, &coplanar, source, target);
                    if(collision) {
                        std::cout << "Collision between : " << object1->model.directory << " and " << object2->model.directory << std::endl;
                        std::cout << "Source : " << source[0] << " - " << source[1] << " - " << source[2] << " - " << std::endl;
                        std::cout << "Target : " << target[0] << " - " << target[1] << " - " << target[2] << " - " << std::endl;
                        glm::vec3 collisionVector(glm::normalize(glm::vec3(target - source)));
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

glm::vec4 planeEquation(Vertex* v1, Vertex* v2, Vertex* v3) {
    float a1 = v2->Position.x - v1->Position.x;
    float b1 = v2->Position.y - v1->Position.y;
    float c1 = v2->Position.z - v1->Position.z;
    float a2 = v3->Position.x - v1->Position.x;
    float b2 = v3->Position.y - v1->Position.y;
    float c2 = v3->Position.z - v1->Position.z;
    float a = b1 * c2 - b2 * c1;
    float b = a2 * c1 - a1 * c2;
    float c = a1 * b2 - b1 * a2;
    float d = (- a * v1->Position.x - b * v1->Position.y - c * v1->Position.z);
    return glm::vec4(a,b,c,d);
}

float sideOfPlane(glm::vec4* p, Vertex* v) {
    float d = p->x * v->Position.x + p->y * v->Position.y + p->z * v->Position.z + p->w;
    return d;
}

bool sameSign(float d1, float d2, float d3) {
    if (d1 > 0 && d2 < 0)
        return false;
    if (d1 < 0 && d2 > 0)
        return false;
    if (d1 > 0 && d3 < 0)
        return false;
    if (d1 < 0 && d3 > 0)
        return false;
    if (d2 > 0 && d3 < 0)
        return false;
    if (d2 < 0 && d3 > 0)
        return false;
    return true;
}

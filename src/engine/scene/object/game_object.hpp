#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "../../../engine/model.hpp"
#include "../../../engine/shader.hpp"
#include "../../../engine/light.hpp"
#include "../../../engine/camera.hpp"
class GameObject {
public:
    GameObject(Model model, Shader shader, Model hitbox);
    GameObject(Model model, Shader shader);

    void toggleGlow();
    void move(glm::vec3 vector);

    inline Model     const& getModel()         const { return _model; }
    inline Shader    const& getShader()        const { return _shader; }
    inline Model     const& getHitbox()        const { return _hitbox; }
    inline glm::vec3 const& getPosition()      const { return _position; }
    inline glm::vec3 const& getUp()            const { return _up; }
    inline glm::vec3 const& getFront()         const { return _front; }
    inline glm::vec3 const& getSpeed()         const { return _speed; }
    inline bool             isGravitable()     const { return _isGravitable; }
    inline bool             isCollisionnable() const { return _isCollisionnable; }
    inline bool             isGlowing()        const { return _isGlowing; }

    inline void setPosition(glm::vec3 newPos)     { _position = newPos; }
    inline void setSpeed(glm::vec3 newSpeed)      { _speed = newSpeed; }
    inline void setGravitable(bool isGravitable)  { _isGravitable = isGravitable; }

private:
    Model  _model;
    Shader _shader;
    Model  _hitbox;

    glm::vec3 _position         = glm::vec3(0.0f);
    glm::vec3 _up               = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _front            = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _speed            = glm::vec3(0.0f);
    bool      _isGravitable     = true;
    bool      _isCollisionnable = true;
    bool      _isGlowing        = false;
};

#endif
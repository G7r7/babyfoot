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

    inline Model     const& getModel()                           const { return _model; }
    inline Shader    const& getShader()                          const { return _shader; }
    inline Model     const& getHitbox()                          const { return _hitbox; }
    inline glm::vec3 const& getPosition()                        const { return _position; }
    inline glm::vec3 const& getSpeed()                           const { return _speed; }
    inline glm::vec3 const& getRotationSpeed()                   const { return _rotationSpeed; }
    inline glm::quat const& getOrientation()                     const { return _orientation; }
    inline float     const& getMass()                            const { return _mass; }
    inline bool             isGravitable()                       const { return _isGravitable; }
    inline bool             isCollisionnable()                   const { return _isCollisionnable; }
    inline bool             isGlowing()                          const { return _isGlowing; }
    glm::mat4               getTransformationMatrix()            const; 
    float                   getKineticEnergy()                   const;
    float                   getMomentOfInertia(glm::vec3 axis, glm::vec3 point) const;

    inline void setPosition(glm::vec3 newPos)           { _position = newPos; }
    inline void setSpeed(glm::vec3 newSpeed)            { _speed = newSpeed; }
    inline void setRotationSpeed(glm::vec3 newSpeed)    { _rotationSpeed = newSpeed; }
    inline void setOrientation(glm::quat newOrientation){ _orientation = newOrientation; }
    inline void setGravitable(bool isGravitable)        { _isGravitable = isGravitable; }

private:
    Model  _model;
    Shader _shader;
    Model  _hitbox;

    glm::vec3 _position         = glm::vec3(0.0f);
    glm::vec3 _speed            = glm::vec3(0.0f);
    glm::quat _orientation      = glm::quat(glm::vec3(0.f));
    glm::vec3 _rotationSpeed    = glm::vec3(0.0f);
    float     _mass             = 1.f;
    bool      _isGravitable     = true;
    bool      _isCollisionnable = true;
    bool      _isGlowing        = false;
};

#endif
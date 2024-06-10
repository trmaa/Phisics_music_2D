#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include"./sphere.hpp"
#include"./window.hpp"

class Object : public Sphere {
public:
    glm::vec2 velocity;

    Object(glm::vec2 c, float r) : Sphere(c, r) {}
    virtual ~Object() = default;

    void move(float dt){
        this->center += this->velocity*dt;
        if(this->center.y > Window::window.getSize().y){
            this->center.y = Window::window.getSize().y;
        }
    }
};

#endif

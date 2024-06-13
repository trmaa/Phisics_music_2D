#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<glm/glm.hpp>
//#include<iostream>
#include"./sphere.hpp"
#include"./window.hpp"

class Object : public Sphere {
public:
    glm::vec2 velocity;

    Object(glm::vec2 c, float r) : Sphere(c, r) {}
    virtual ~Object() = default;

    void move(float dt){
        this->center += this->velocity*dt;
        if(
            this->equation(glm::vec2(this->center.x,Window::window.getSize().y))//need a fix 
            || this->center.y>Window::window.getSize().y-this->radius
        ){
            this->velocity *= glm::vec2(0,-0.6f);
            this->center.y = Window::window.getSize().y-this->radius;
        }
        //std::cout<<this->equation(glm::vec2(this->center.x,Window::window.getSize().y));
    }
};

#endif

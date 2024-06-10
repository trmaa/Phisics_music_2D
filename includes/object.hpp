#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include "./sphere.hpp"

class Object : public Sphere {
public:
    Object(glm::vec2 c, float r) : Sphere(c, r) {}
    virtual ~Object() = default;
};

#endif

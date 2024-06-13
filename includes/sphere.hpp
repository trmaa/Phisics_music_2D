#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

struct Sphere {
    glm::vec2 center;
    float radius;

    Sphere(glm::vec2 c, float r) : center(c), radius(r) {}

    bool equation(glm::vec2 point) {
        float val = glm::dot(point, point);
        return (val < radius * radius) ? true : false;
    }
};

#endif

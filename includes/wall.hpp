#ifndef WALL_HPP
#define WALL_HPP

#include <glm/glm.hpp>
#include "./sphere.hpp"

class Wall : public Sphere {
public:
    Wall(glm::vec2 c, float r) : Sphere(c, r) {}
    virtual ~Wall() = default;
};

#endif

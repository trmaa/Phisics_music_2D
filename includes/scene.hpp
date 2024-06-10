#ifndef SCENE_HPP
#define SCENE_HPP

#include<vector>
#include"./object.hpp"
#include"./wall.hpp"
#include"./json.hpp"

class Scene {
private:
    static nl::json read_json(const std::string& file_path);
public:
    static std::vector<Object> object;
    static std::vector<Wall> wall;
public:
    static void load(const std::string& file_path);
};

#endif

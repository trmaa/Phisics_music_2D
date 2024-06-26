#include<fstream>
#include<future>
#include <glm/geometric.hpp>
#include<iostream>
#include"../includes/json.hpp"
#include"../includes/scene.hpp"

float Scene::gravity = -98.066f;
float Scene::friction = 1.f;
std::vector<Object> Scene::object;
std::vector<Wall> Scene::wall;

nl::json Scene::read_json(const std::string& file_path) {
    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return "";
    }

    nl::json j;
    input_file >> j;

    return j;
}

void Scene::load(const std::string& file_path) {
    std::future<nl::json> jj = std::async(std::launch::async, read_json, file_path);
    nl::json j = jj.get();

	if (j.contains("object")) {
        for (const auto& obj : j["object"]) {
            glm::vec3 center(obj["center"][0], obj["center"][1], obj["center"][2]);
            float radius = obj["radius"];
            object.emplace_back(center, radius);
        }
    }

    if (j.contains("wall")) {
        for (const auto& wll : j["wall"]) {
            glm::vec2 center(wll["center"][0], wll["center"][1]);
            float radius = wll["radius"];
            wall.emplace_back(center, radius);
        }
    }
}

void Scene::update(float dt){
    for(unsigned int i = 0; i < Scene::object.size(); i++){
        Object *obj = &Scene::object[i];
        obj->velocity += glm::vec2(0,-Scene::gravity); 
        for(unsigned int j = 0; j < Scene::wall.size(); j++){
            Wall *wall = &Scene::wall[j];
            glm::vec2 dir = obj->center-wall->center;
            float dis = std::sqrt(glm::dot(dir,dir));

            if(dis>wall->radius-obj->radius){
                //obj->center = wall->center+glm::normalize(dir)*glm::vec2(wall->radius-obj->radius);
                obj->velocity -= dir;
                obj->velocity *= 0.95f;
            }
        }
        for(unsigned int j = 0; j < Scene::object.size(); j++){
            if(i==j){
                continue;
            }
            Object *obj2 = &Scene::object[j];
            glm::vec2 dir = obj->center-obj2->center;
            float dis = std::sqrt(glm::dot(dir,dir));

            if(dis<obj->radius+obj2->radius){
                obj->center = obj2->center+dir;
                obj2->center = obj->center-dir;
                obj->velocity -= -dir;//obj2->velocity*glm::normalize(dir);
                obj2->velocity -= dir;//obj->velocity*glm::normalize(dir);
            }
        }
        obj->move(dt);
    } 
}

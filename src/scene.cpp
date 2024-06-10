#include<fstream>
#include<iostream>
#include"../includes/json.hpp"
#include"../includes/scene.hpp"

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
	nl::json j = read_json(file_path);
	
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

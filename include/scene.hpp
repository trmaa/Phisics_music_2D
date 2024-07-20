#ifndef SCENE_HPP
#define SCENE_HPP

#include "json.hpp"
//#include "sound.hpp"
#include <cmath>
#include <fstream>
#include <future>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>

struct Object {
	glm::vec2 velocity;
	glm::vec2 position;
	float radius;


	Object(glm::vec2 p, float r)
		: position(p) {
		this->velocity = glm::vec2(0);
		this->radius = r;
	}
};

class Scene {
private:
	Object _wall;
	std::vector<Object> _object;

private:
	static nl::json readJson(const std::string& fpath) {
		std::ifstream file(fpath);
		if (!file.is_open()) {
			std::cerr<<"Json corrupt"<<std::endl;
			return "";
		}
		nl::json data;
		file >> data;
		return data;
	}

public:
	const Object& wall() { return this->_wall; }
	const std::vector<Object>& object() { return this->_object; }

	Scene(const std::string& fpath, float w, float h): _wall(glm::vec2(w/2, h/2), h/2) {
		std::future<nl::json> raw = std::async(std::launch::async, Scene::readJson, fpath);
		nl::json data = raw.get();
		if (!data.contains("object"))
			return;
		for (const auto& obj : data["object"]) {
			glm::vec2 center(obj["center"][0], obj["center"][1]);
			float radius = obj["radius"];
			this->_object.emplace_back(center, radius);
		}
	}
	~Scene() = default;

public:
	void update(float dt) {
		for (Object& object : this->_object) {
			object.velocity.y += 9.8066f;

			//if object colides with the wall
			glm::vec2 rltp = object.position-this->_wall.position;
			if (this->_wall.radius-object.radius < std::sqrt(glm::dot(rltp, rltp))) {
				object.position = glm::normalize(rltp)*(this->_wall.radius-object.radius) + this->_wall.position;
				
				object.velocity = std::sqrt(glm::dot(object.velocity, object.velocity))*glm::normalize(-rltp);	
				
				//make_sound(220,0.01f);
			}
			//if object colides with object
			for (Object& object2 : this->_object) {
				if (&object == &object2) {
					continue;
				}
				glm::vec2 rltp = object.position-object2.position;
				glm::vec2 rltp2 = object2.position-object.position;
				if (object2.radius+object.radius > std::sqrt(glm::dot(rltp, rltp))) {
					object.position = glm::normalize(rltp)*(object.radius+object2.radius) + object2.position;
					object2.position = glm::normalize(rltp2)*(object.radius+object2.radius) + object.position;
				
					glm::vec2 nv = object.velocity;
					object.velocity = std::sqrt(glm::dot(object2.velocity, object2.velocity))*glm::normalize(rltp);
					object2.velocity = std::sqrt(glm::dot(nv, nv))*glm::normalize(rltp2);

					//make_sound(220,0.01f);
				}
			}


			object.position += object.velocity * dt;	
		}
	}
};

#endif

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "scene.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>

class Window: public sf::RenderWindow {
private:
	glm::ivec2 _viewport;

public:
	const glm::ivec2& viewport() { return this->_viewport; }

	Window(int w, int h)
		: _viewport(w, h) {
		this->create(sf::VideoMode(w, h), "window", sf::Style::Fullscreen);
	}
	~Window() = default;

public:
	void repaint(Scene& scene) {
		this->clear();
		
		sf::CircleShape shape;
		shape.setFillColor(sf::Color(0,0,0));
		shape.setOutlineColor(sf::Color(255,255,255));
		shape.setOutlineThickness(10.f);
		shape.setRadius(scene.wall().radius-20.f);
		shape.setPosition(scene.wall().position.x, scene.wall().position.y+10.f);
		shape.setOrigin(scene.wall().radius, scene.wall().radius);
		this->draw(shape);

		for (Object object : scene.object()) {
			sf::CircleShape shape;
			shape.setRadius(object.radius);
			shape.setPosition(object.position.x, object.position.y);
			shape.setOrigin(object.radius, object.radius);
			this->draw(shape);
		}
		
		this->display();
	}
};

#endif

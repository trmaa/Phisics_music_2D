#include "window.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <glm/glm.hpp>

void loop();

Window window(1920,1080);
Scene scene("./bin/scene.json", 1920, 1080);

sf::Clock cloc;
sf::Time timeElapsed;
float deltaTime;

int main() {
	sf::Event ev;
	while (window.isOpen()) {
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}
		timeElapsed = cloc.restart();
		deltaTime = timeElapsed.asSeconds();

		loop();
	}
}

void loop() {
	window.repaint(scene);
	scene.update(deltaTime);
}

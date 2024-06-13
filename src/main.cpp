#include<SFML/Graphics.hpp>
#include<SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include<glm/glm.hpp>
#include"../includes/window.hpp"
#include"../includes/scene.hpp"

void loop(float dt){
    Window::repaint(dt);
    Scene::update(dt);
}

int main(){
	Window::open();
    Scene::load("./scene.json");

    sf::sleep(sf::seconds(1.f));

    sf::Clock clock;
	while(Window::window.isOpen()){
        sf::Event event;
        while(Window::window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                Window::window.close();
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                Window::window.setView(sf::View(visibleArea));
            }
        }
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

		loop(dt);
	}
}

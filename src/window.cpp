#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Color.hpp>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<glm/glm.hpp>
#include"../includes/window.hpp"
#include"../includes/scene.hpp"

sf::Font Window::m_font;
sf::Text Window::m_fpsText;
sf::RenderWindow Window::window;
	
void Window::open(){
	Window::window.create(sf::VideoMode(1280, 720), "SFML works!");
	
	if(!Window::m_font.loadFromFile("./fonts/pixelmix.ttf")) {
		std::cerr<<"There is no font";
	}

	Window::m_fpsText.setFont(Window::m_font);
	Window::m_fpsText.setCharacterSize(24);
	Window::m_fpsText.setFillColor(sf::Color::White);
	Window::m_fpsText.setPosition(10.f, 10.f);

    Window::window.setFramerateLimit(60);
}

void Window::repaint(float dt){
    float fps = 1.f / dt;
    Window::m_fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

    Window::window.clear();

    for(unsigned int i = 0; i < Scene::object.size(); i++){
        sf::CircleShape shape(Scene::object[i].radius);
        shape.setPosition(
            Scene::object[i].center.x - Scene::object[i].radius, 
            Scene::object[i].center.y - Scene::object[i].radius
        );
        shape.setFillColor(sf::Color::White); 
        Window::window.draw(shape);    
    }
   
    for(unsigned int i = 0; i < Scene::wall.size(); i++){
        sf::CircleShape shape(Scene::wall[i].radius);
        shape.setPosition(
            Scene::wall[i].center.x - Scene::wall[i].radius, 
            Scene::wall[i].center.y - Scene::wall[i].radius
        );
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(4);
        shape.setOutlineColor(sf::Color::White);
        Window::window.draw(shape);    
    }

    Window::window.draw(Window::m_fpsText);
    Window::window.display();
}

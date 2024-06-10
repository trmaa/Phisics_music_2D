#include <SFML/Graphics/Color.hpp>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<glm/glm.hpp>
#include"../includes/window.hpp"

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
}

void Window::repaint(float dt){
	float fps = 1.f/dt;
	Window::m_fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

	Window::window.clear();
	Window::window.draw(Window::m_fpsText);
	Window::window.display();
}

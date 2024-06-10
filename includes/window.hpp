#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<SFML/Graphics.hpp>
#include<cmath>
#include<glm/glm.hpp>

class Window{
private:	
	static sf::Font m_font;
	static sf::Text m_fpsText;
public:
	static sf::RenderWindow window;
public:
	static void open();
	static void repaint(float dt);
};

#endif

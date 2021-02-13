#pragma once

#include "SFML\Graphics.hpp"
#include "iostream"

class Button
{
public:
	sf::RectangleShape buttonBG;
	sf::Text buttonText;

	bool bPressed, bReleased, bClicked, bHighlighted;

	Button();
	Button(sf::Vector2f size, sf::Color color, std::string string);
	~Button();

	bool isHighlighted();

	void hightlight(sf::RenderWindow* window);
	void update(sf::Event event, float deltatime);
	void render(sf::RenderWindow* window, float deltatime);
	void checkPressed(sf::Event event);

private:
	sf::Color defaultColor;
	sf::Color highlightedColor; 
};


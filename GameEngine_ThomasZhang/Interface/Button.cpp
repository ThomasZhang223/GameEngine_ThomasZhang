#include "Button.h"

Button::Button()
{
}

Button::Button(sf::Vector2f size, sf::Color color, std::string string)
{
	bPressed = false;
	bReleased = false;
	bClicked = false; 
	bHighlighted = false;

	defaultColor = sf::Color(color);
	highlightedColor = sf::Color(defaultColor.r + 50, defaultColor.g + 50, defaultColor.b + 50, 255);	

	buttonBG.setSize(size);
	buttonBG.setFillColor(defaultColor);
	buttonBG.setPosition(sf::Vector2f(0,0));

	buttonText.setCharacterSize(12);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(sf::Vector2f(0, 0));
	buttonText.setString(string);
}

Button::~Button()
{
}

bool Button::isHighlighted()
{
	return bHighlighted;
}

void Button::highlight(sf::RenderWindow* window)
{
	bHighlighted = buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
	
	if (bHighlighted)
	{
		buttonBG.setFillColor(sf::Color(highlightedColor));
		this->bHighlighted = true;
	}
	else
	{
		buttonBG.setFillColor(sf::Color(defaultColor));
		this->bHighlighted = false;
	}
}

void Button::update(sf::Event event, float deltatime)
{
	checkPressed(event);
}

void Button::render(sf::RenderWindow* window, float deltatime)
{
	window->draw(buttonBG);
	window->draw(buttonText);
	window->display();
}

void Button::checkPressed(sf::Event event)
{
	if (bHighlighted)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				bPressed = true;
			}
			else
			{
				bPressed = false;
				bClicked = false;
			}
		}
		if (bPressed == true)
		{
			if (event.type == sf::Event::MouseButtonReleased)
			{
				bReleased = true;
				bClicked = true;
			}
		}
		else
		{
			bReleased = false;
			bClicked = false;
		}
	}
}

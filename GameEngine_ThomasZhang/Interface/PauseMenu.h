#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ButtonMap.h"
#include "States.h"

class PauseMenu
{
public:
	PauseMenu();
	PauseMenu(sf::RenderWindow *Window);

	~PauseMenu();
	
	void Update(sf::Event event, float deltatime, sf::RenderWindow *Window);

	void Render(sf::RenderWindow* Window, float deltatime, sf::Vector2f resumePosition);

private:
	void initButton();

	void quit(sf::Window* Window);
};


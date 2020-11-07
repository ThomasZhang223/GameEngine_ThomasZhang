
#include "Engine.h"

Engine& Engine::GetInstance(void)
{
	static Engine instance;

	return instance;
}

void Engine::Start(sf::RenderWindow* win)
{
	bQuit = false; 
	this->window = win; 
	
	while (this->window->isOpen() == true)
	{
		Update();
	}
}

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
}

void Engine::Update()
{
	sf::Event event;

	while (window->pollEvent(event) == true)
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}


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

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}

void Engine::Update()
{
	sf::Event event;

	//listen to any event occurring while the program is running
	while (window->pollEvent(event) == true)
	{
		//close requested event
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
	}

	world->tick(10.0f);
}

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
}

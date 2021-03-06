
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

	mainCamera = MainCamera(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));

	pauseMenu = PauseMenu(this->window);

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
			exit(EXIT_SUCCESS);
		}

		pauseMenu.Update(event, 10.0f, window);
	}

	world->tick(10.0f);

	mainCamera.update(world, 10.0f, window);

	if (States::GetPausedState())
	{
		
		gameInactiveStateAction();
	}
}

void Engine::gameInactiveStateAction()
{
	pauseMenu.Render(window, 10.0f, mainCamera.cameraView.getCenter());
}

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
}

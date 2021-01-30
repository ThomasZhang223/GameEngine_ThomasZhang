#include "InputSystem.h"

InputSystem::InputSystem(sf::RenderWindow* win) : window(win)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	getKeyEvents(world);
}

void InputSystem::getKeyEvents(ECS::World* world)
{
	world->each<struct InputController>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input)->void
		{
			input->wKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			input->aKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			input->sKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			input->dKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		});
}

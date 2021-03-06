#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"
#include "Components.h"
#include "Interface/MainCamera.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderingSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Interface/MainCamera.h"
#include "Interface/PauseMenu.h"
#include "Interface/States.h"
#include "Interface/ButtonMap.h"
#include "Interface/Button.h"
	
class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world; 

	MainCamera mainCamera;
	PauseMenu pauseMenu; 

	static Engine& GetInstance(void);

	void Start(sf::RenderWindow* win);
	void AddSystem(ECS::EntitySystem* newSys);

private:
	bool bQuit;

	Engine(void);
	// required to prevent the reference from being copied, moved, or assigned 
	// (only one instance of the engine can be run)
	Engine(Engine& copy);				// hide copy constructor
	Engine(Engine&& other);				// hide move constructor 
	Engine& operator= (Engine& copy);	// hide assignment operator

	~Engine(void);

	void Update();
	void gameInactiveStateAction();
};

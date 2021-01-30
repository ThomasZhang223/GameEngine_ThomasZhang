#include "MainCamera.h"

MainCamera::MainCamera()
{
}

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

MainCamera::~MainCamera()
{
}

void MainCamera::update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow)
{
	sf::Vector2f windowSize(gameWindow->getSize().x, gameWindow->getSize().y);
	cameraView.setSize(windowSize);
	float cameraMoveSpeed = 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cameraView.move(-cameraMoveSpeed * deltaTime, 0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cameraView.move(cameraMoveSpeed * deltaTime, 0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cameraView.move(0, -cameraMoveSpeed * deltaTime);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cameraView.move(0, cameraMoveSpeed * deltaTime);
	}

	gameWindow->setView(cameraView);
}

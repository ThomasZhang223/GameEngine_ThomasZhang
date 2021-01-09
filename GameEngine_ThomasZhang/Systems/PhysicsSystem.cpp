#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	ECS::ComponentHandle<BoxCollider> touchedEntity, 
	float x, float y)
{
	if (touchingEntity->rightEdge + x > touchedEntity->leftEdge && 
		touchedEntity->rightEdge > touchingEntity->leftEdge + x)
	{
		if (touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
			touchedEntity->bottomEdge > touchingEntity->topEdge + y)
		{
			return true;
		}
	}
}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	sf::RectangleShape touchedRectangle, float x, float y)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight= touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;

	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;

	return touchingEntity->rightEdge> touchedRectLeft &&
		touchedRectRight > touchingEntity->leftEdge &&
		touchingEntity->bottomEdge > touchedRectTop &&
		touchedRectBottom > touchingEntity->topEdge;
}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	return touchingEntity->rightEdge > touchedEntity->leftEdge && touchedEntity->rightEdge > touchingEntity->leftEdge;
}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<Transform> transform, 
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	if (touchingEntity->rightEdge + transform->xSpeed > touchedEntity->leftEdge &&
		touchingEntity->topEdge<touchedEntity->bottomEdge && 
		touchingEntity->bottomEdge>touchedEntity->topEdge && 
		transform->xSpeed > 0)
	{
		transform->xSpeed = 0;
	}

	if (touchingEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
		touchingEntity->leftEdge<touchedEntity->rightEdge &&
		touchingEntity->rightEdge>touchedEntity->leftEdge &&
		transform->ySpeed > 0)
	{
		transform->ySpeed = 0;
	}

	if (touchingEntity->leftEdge + transform->xSpeed < touchedEntity->rightEdge &&
		touchingEntity->bottomEdge>touchedEntity->topEdge &&
		touchingEntity->topEdge<touchedEntity->bottomEdge &&
		transform->xSpeed < 0)
	{
		transform->xSpeed = 0;
	}

	if (touchingEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
		touchingEntity->leftEdge<touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge &&
		transform->ySpeed < 0)
	{
		transform->ySpeed = 0;
	}

}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<Transform> transform, 
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	sf::RectangleShape touchedRectangle)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;

	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;

	if (touchingEntity->rightEdge + transform->xSpeed > touchedRectLeft &&
		touchingEntity->topEdge<touchedRectBottom &&
		touchingEntity->bottomEdge>touchedRectTop &&
		transform->xSpeed > 0)
	{
		transform->xSpeed = 0;
	}

	if (touchingEntity->bottomEdge + transform->ySpeed > touchedRectTop &&
		touchingEntity->leftEdge<touchedRectRight&&
		touchingEntity->rightEdge>touchedRectLeft &&
		transform->ySpeed > 0)
	{
		transform->ySpeed = 0;
	}

	if (touchingEntity->leftEdge + transform->xSpeed < touchedRectRight &&
		touchingEntity->bottomEdge>touchedRectTop &&
		touchingEntity->topEdge < touchedRectBottom &&
		transform->xSpeed < 0)
	{
		transform->xSpeed = 0;
	}

	if (touchingEntity->bottomEdge + transform->ySpeed >touchedRectTop &&
		touchingEntity->leftEdge<touchedRectRight &&
		touchingEntity->rightEdge > touchedRectLeft &&
		transform->ySpeed < 0)
	{
		transform->ySpeed = 0;
	}

}

void PhysicsSystem::checkCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
	ECS::ComponentHandle<Transform> touchingTransform = touchingEntity->get<Transform>(), touchedTransform = touchedEntity->get<Transform>();

	if ((touchingTransform->xPos - touchingTransform->xSpeed) < (touchedTransform->xPos - touchingTransform->xSpeed))
	{
		touchedTransform->xPos++;
	}

	else if ((touchingTransform->xPos - touchingTransform->xSpeed) > (touchedTransform->xPos - touchingTransform->xSpeed))
	{
		touchedTransform->xPos--;
	}

	if ((touchingTransform->yPos - touchingTransform->ySpeed) < (touchedTransform->yPos - touchingTransform->ySpeed))
	{
		touchedTransform->yPos++;
	}

	if ((touchingTransform->yPos - touchingTransform->ySpeed) > (touchedTransform->yPos - touchingTransform->ySpeed))
	{
		touchedTransform->yPos--;
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltatime)
{
}

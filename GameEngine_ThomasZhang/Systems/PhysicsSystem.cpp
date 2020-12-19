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

	return touchingEntity->rightEdge + x > touchedRectLeft &&
		touchedRectRight > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedRectTop &&
		touchedRectBottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	return false;
}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<Transform> transform, 
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{

}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<Transform> transform, 
	ECS::ComponentHandle<BoxCollider> touchingEntity, 
	sf::RectangleShape touchedRectangle)
{
}

void PhysicsSystem::checkCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
}

void PhysicsSystem::tick(ECS::World* world, float deltatime)
{
}

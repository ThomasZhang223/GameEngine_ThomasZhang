#pragma once

#include "../Engine.h"

class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity,
		float x, float y
	);

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		sf::RectangleShape touchedRectangle,
		float x, float y
	);

	bool isColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity
	);

	void checkCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity
	);

	void checkCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		sf::RectangleShape touchedRectangle
	);

	void PushEntity(
		ECS::Entity* touchingEntity,
		ECS::Entity* touchedEntity
	);

	void tick(ECS::World* world, float deltatime) override;
};
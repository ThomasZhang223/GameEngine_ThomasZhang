#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<struct BoxCollider> touchingEntity, 
	ECS::ComponentHandle<struct BoxCollider> touchedEntity, 
	float x, float y)
{
	return touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
		touchedEntity->bottomEdge > touchingEntity->topEdge + y;

}

bool PhysicsSystem::isColliding(
	ECS::ComponentHandle<struct BoxCollider> touchingEntity, 
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
	ECS::ComponentHandle<struct BoxCollider> touchingEntity, 
	ECS::ComponentHandle<struct BoxCollider> touchedEntity)
{
	return touchingEntity->rightEdge > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge &&
		touchedEntity->bottomEdge > touchingEntity->topEdge;
}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<struct Transform> transform, 
	ECS::ComponentHandle<struct BoxCollider> touchingEntity, 
	ECS::ComponentHandle<struct BoxCollider> touchedEntity)
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

	if (touchingEntity->topEdge + transform->ySpeed > touchedEntity->bottomEdge &&
		touchingEntity->leftEdge<touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge &&
		transform->ySpeed < 0)
	{
		transform->ySpeed = 0;
	}

}

void PhysicsSystem::checkCollisionSides(
	ECS::ComponentHandle<struct Transform> transform, 
	ECS::ComponentHandle<struct BoxCollider> touchingEntity, 
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

void PhysicsSystem::PushEntity(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
	float newTouchingX = touchingEntity->get<struct Transform>()->xPos;
	float newTouchingY = touchingEntity->get<struct Transform>()->yPos;

	float touchedX = touchedEntity->get<struct Transform>()->xPos;
	float touchedY = touchedEntity->get<struct Transform>()->yPos;

	float xSpeed = touchingEntity->get<struct Transform>()->xSpeed;
	float ySpeed = touchingEntity->get<struct Transform>()->ySpeed;

	if (xSpeed > 0 && newTouchingX <= touchedX)
	{
		touchedEntity->get<struct Transform>()->xPos++;
	}
	else if (xSpeed < 0 && newTouchingX >= touchedX)
	{
		touchedEntity->get<struct Transform>()->xPos--;
	}
	if (ySpeed > 0 && newTouchingY <= touchedY)
	{
		touchedEntity->get<struct Transform>()->yPos++;
	}
	else if (ySpeed < 0 && newTouchingY >= touchedY)
	{
		touchedEntity->get<struct Transform>()->yPos--;
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltatime)
{
	world->each<struct BoxCollider, struct Sprite2D, struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct BoxCollider> box,
			ECS::ComponentHandle<struct Sprite2D> sprite,
			ECS::ComponentHandle<struct Transform> transform
		) -> void 
	{
		box->Update(transform->xPos, transform->yPos,
			sprite->sprite.getTextureRect().width,
			sprite->sprite.getTextureRect().height);
	});

	world->each<struct BoxCollider, struct Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<struct BoxCollider> touchingBox,
			ECS::ComponentHandle<struct Transform> transform1
			)->void
		{
			world->each<struct BoxCollider, struct Transform>(
				[&](ECS::Entity* touchedEntity,
					ECS::ComponentHandle<struct BoxCollider> touchedBox,
					ECS::ComponentHandle<struct Transform> transform2
					) -> void
				{
					// statement to avoid comparing same entity to itself
					if (touchingEntity->getEntityId() != touchedEntity->getEntityId())
					{
						// initial collision check
						if (isColliding(touchingBox, touchedBox) == true)
						{
							//final collision check
							PushEntity(touchingEntity, touchedEntity);
						}
					}
				});
		});

	world->each<struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct Transform> transform
			) -> void
	{
		transform->move();
	});
}

#include "MovementSystem.h"

#define X_SPEED 0.1
#define Y_SPEED 0.1

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<InputController, Transform, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Animator> animator) -> void
	{
			if (input->inputActive == true)
			{
				if (input->wKey == true)
				{
					transform->ySpeed = -Y_SPEED;
					transform->move();
				}
				else if (input->sKey == true)
				{
					transform->ySpeed = Y_SPEED;
					transform->move();
				}
				else
				{
					transform->ySpeed = 0;
				}

				if (input->aKey == true)
				{
					animator->isFacingRight = false;
					animator->currentRow = 1;
					transform->xSpeed = -X_SPEED;
					transform->move();
				}
				else if (input->dKey == true)
				{
					animator->isFacingRight = true;
					animator->currentRow = 1;
					transform->xSpeed = X_SPEED;
					transform->move();
				}
				else
				{
					animator->currentRow = 0;
					transform->xSpeed = 0;
				}

			}
	});
}

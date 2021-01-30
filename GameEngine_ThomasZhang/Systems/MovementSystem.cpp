#include "MovementSystem.h"

//#define X_SPEED 0.1
//#define Y_SPEED 0.1

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<struct InputController, struct Transform, struct Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input,
			ECS::ComponentHandle<struct Transform> transform,
			ECS::ComponentHandle<struct Animator> animator) -> void
	{
			if (input->inputActive == true)
			{
				if (input->wKey == true)
				{
					transform->ySpeed = -transform->ySpeedMod;
					transform->move();
				}
				else if (input->sKey == true)
				{
					transform->ySpeed = transform->ySpeedMod;
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
					transform->xSpeed = -transform->xSpeedMod;
					transform->move();
				}
				else if (input->dKey == true)
				{
					animator->isFacingRight = true;
					animator->currentRow = 1;
					transform->xSpeed = transform->xSpeedMod;
					transform->move();
				}
				else
				{
					animator->currentRow = 0;
					transform->xSpeed = 0;
				}

			}

			std::printf("X: %f\nY: %f\n", transform->xPos, transform->yPos);
			std::printf("XVEL: %f\nYVEL: %f\n", transform->xSpeed + transform->xSpeedMod, transform->ySpeed + transform->ySpeedMod);
	});
}

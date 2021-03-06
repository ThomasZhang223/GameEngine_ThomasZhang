#include "AnimationSystem.h"

AnimationSystem::AnimationSystem(void)
{
}

AnimationSystem::~AnimationSystem(void)
{
}

void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<struct Animator, struct Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<struct Animator> animator,
				ECS::ComponentHandle<struct Sprite2D> sprite)->void
			{
				// set timer for animator
				animator->currentTime += deltaTime;

				// set animation forward and reset to first frame to loop
				if (animator->currentTime >= animator->nextTimeFrame)
				{
					animator->currentTime = 0;

					// run through the animation spritesheet regardless of column or row
					animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumn;
				}

				sprite->sprite.setTextureRect(
					sf::IntRect(
						animator->currentColumn * animator->frameWidth,
						animator->currentRow * animator->frameHeight,
						animator->frameWidth,
						animator->frameHeight));
			});
	}
}

#include "AnimationSystem.h"

AnimationSystem::AnimationSystem(void)
{
}

AnimationSystem::~AnimationSystem(void)
{
}

void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<Animator, Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Animator> animator,
			ECS::ComponentHandle<Sprite2D> sprite)->void
	{
			sprite->sprite.setTextureRect(
				sf::IntRect(animator->currentColumn * animator->frameWidth,
					animator->currentRow * animator->frameHeight,
					animator->frameWidth, animator->frameHeight));

	});
}

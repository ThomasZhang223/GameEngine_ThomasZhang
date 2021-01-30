#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(void)
{
}

RenderingSystem::~RenderingSystem(void)
{
}


void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	Engine::GetInstance().window->clear();

	world->each<struct Transform, struct Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct Transform> transform,
			ECS::ComponentHandle<struct Sprite2D> sprite)->void
		{
			if (textureMap.count(sprite->texture) < 1)
			{
				textureMap[sprite->texture] = LoadTexture(sprite->texture);
			}

			if (sprite->sprite.getTexture() == nullptr)
			{
				sprite->sprite.setTexture(*textureMap[sprite->texture]);
				sprite->width = sprite->sprite.getGlobalBounds().width;
				sprite->height = sprite->sprite.getGlobalBounds().height;
			}

			sprite->sprite.setPosition(transform->xPos, transform->yPos);

			Engine::GetInstance().window->draw(sprite->sprite);
		});

	Engine::GetInstance().window->display();
}

sf::Texture* RenderingSystem::LoadTexture(std::string texturePath)
{
	sf::Texture* texture = new sf::Texture();

	if (texture->loadFromFile(texturePath) == false)
	{
		std::cerr << "Error: unable to load image" << texturePath << "./nIs this image in the correct directory?" << std::endl;

		system("pause");
		exit(EXIT_FAILURE);
	}

	return texture;
}


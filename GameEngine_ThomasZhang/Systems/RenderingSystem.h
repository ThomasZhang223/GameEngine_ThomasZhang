#pragma once

#include "../Engine.h"

class RenderingSystem : public ECS::EntitySystem
{
public:
	RenderingSystem(void);
	~RenderingSystem(void);

	void tick(ECS::World* world, float deltaTime) override; 

private:
	//this is a dynamic list with generic types of a Key(string) and a Value(Texture*), respectively, called textureMap
	std::unordered_map<std::string, sf::Texture*> textureMap;
	
	sf::Texture* LoadTexture(std::string texture);
};


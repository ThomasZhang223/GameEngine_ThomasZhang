#include "TileMapSystem.h"

TileMapSystem::TileMapSystem()
{
}

TileMapSystem::~TileMapSystem()
{
}

void TileMapSystem::tick(ECS::World* world, float deltaTime)
{
	Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<TileMap> tileMap) -> void
		{
			if (States::GetPausedState() == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					addTileOnClick(true, tileMap);
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					addTileOnClick(false, tileMap);
				}
			}

			if (ButtonMap::GetMap()["SAVE"]->bClicked)
			{
				tileMap->saveTileMap("TILETEST.TXT");
				ButtonMap::GetMap()["SAVE"]->bClicked= false;
			}
			if (ButtonMap::GetMap()["LOAD"]->bClicked)
			{
				tileMap->loadTileMap("TILETEST.TXT");
				ButtonMap::GetMap()["LOAD"]->bClicked = false;
			}
		});
}

void TileMapSystem::addTileOnClick(bool bHadCollision, ECS::ComponentHandle<TileMap> tileMap)
{
	// reference for windows pointer that is used below to determine active curser position for adding tiles
	sf::RenderWindow* winRef = Engine::GetInstance().window;
	sf::Vector2f mousePosView = winRef->mapPixelToCoords(sf::Mouse::getPosition(*winRef));
	sf::Vector2i mousePosGrid(static_cast<int>(mousePosView.x / tileMap->gridSizeF), static_cast<int>(mousePosView.y / tileMap->gridSizeF));
	tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, bHadCollision);

}

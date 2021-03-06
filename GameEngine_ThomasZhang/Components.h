#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"
#include "Interface/Tile.h"
#include <fstream>

struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;
	float xSpeed, ySpeed, speedMod;

	Transform(float x, float y, float newSpeedMod = 0.0f, float newXspeed = 0.0f, float newYSpeed = 0.0f) 
	{
		xPos = x; 
		yPos = y;

		speedMod = newSpeedMod;

		xSpeed = 0;
		ySpeed = 0;

		rotation = 0.0f;
	}

	void updateSpeed(float x, float y)
	{
		xSpeed = x;
		ySpeed = y;
	}

	void move()
	{
		if (xSpeed!= 0 && ySpeed!= 0)
		{
			xSpeed /= 2;
			ySpeed /= 2;
		}
		xPos += xSpeed;
		yPos += ySpeed;
	}

	void stop()
	{
		xSpeed = 0;
		ySpeed = 0;
	}
};
ECS_DEFINE_TYPE(Transform);

struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite sprite;
	std::string texture;
	unsigned int width, height;

	Sprite2D(std::string filepath)
	{
		texture = filepath;
	}
};
ECS_DEFINE_TYPE(Sprite2D);


struct Animator
{
public:
	ECS_DECLARE_TYPE;

	int frameWidth, frameHeight;
	int currentColumn, currentRow;
	int totalColumn, totalRow;

	float currentTime, nextTimeFrame;

	bool isFacingRight;

	Animator(int newWidth, int newHeight, float timeBetweenFrames, int newColumn, int newRows)
	{
		this->frameWidth = newWidth;
		this->frameHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		this->nextTimeFrame = timeBetweenFrames;
		this->totalColumn = newColumn;
		this->totalRow = newRows;

		currentTime = 0;

		isFacingRight = true;
	}
};
ECS_DEFINE_TYPE(Animator);

struct InputController
{
public:
	ECS_DECLARE_TYPE;

	bool inputActive; 

	// key states
	bool wKey, aKey, sKey, dKey;

	InputController()
	{
		inputActive = true;

		wKey = false; 
		dKey = false;
		aKey = false;
		sKey = false;
	}
};
ECS_DEFINE_TYPE(InputController);

struct BoxCollider
{
public:
	ECS_DECLARE_TYPE;

	float leftEdge, rightEdge, topEdge, bottomEdge, boxWidth, boxHeight;

	BoxCollider()
	{
		this->leftEdge = 0;
		this->rightEdge = 0;
		this->topEdge = 0;
		this->bottomEdge = 0;
		this->boxWidth = 0;
		this->boxHeight = 0;

		//std::memset(this, '\0', sizeof(BoxCollider));
	}

	void Update(float xSide, float ySide, float width, float height)
	{
		this->leftEdge = xSide;
		this->rightEdge = xSide + width;
		this->topEdge = ySide;
		this->bottomEdge = ySide + height;
		this->boxWidth = width;
		this->boxHeight = height;
	}
};
ECS_DEFINE_TYPE(BoxCollider);

struct Camera
{
public:
	ECS_DECLARE_TYPE;

	sf::View cameraView;
	
	Camera(sf::Vector2f pivot)
	{
		cameraView.setCenter(pivot);
	}
};
ECS_DEFINE_TYPE(Camera);

struct TileMap
{
public:
	ECS_DECLARE_TYPE;

	float gridSizeF; // setting the size of the grid
	uint32_t gridSizeU; 
	uint32_t layers; // rendering images in an order

	sf::Vector2f maxSize; // sets the size of each tile
	sf::RectangleShape collisionBox; // box outline of the tile

	std::vector<std::vector<std::vector<Tile*>>> map;

	TileMap()
	{
		this->gridSizeF = 50.0f;
		this->gridSizeU = static_cast<uint32_t>(this->gridSizeF); // return value of new type (float -> uint
		this->layers = 1;
		this->maxSize.x = 20;
		this->maxSize.y = 20;
		this->map.resize(this->maxSize.x);
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());
			
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y);
				this->map[x].push_back(std::vector<Tile*>());
				
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(nullptr);
				}
			}
		}

		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color(0, 255, 0, 50));
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(-1.0f);
	}

	~TileMap()
	{
		clear();
	}

	void addTile(const int x, const int y, const int z, bool bHasCollision)
	{
		if (x < this->maxSize.x && x >= 0 &&
			y < this->maxSize.y && y >= 0 &&
			z < this->layers && z >= 0)
		{
			if (this->map[x][y][z] == NULL)
			{
				this->map[x][y][z] = new Tile(x, y, this->gridSizeF, bHasCollision);
				printf("added tile\n");
			}
		}
	}
	 
	void clear()	
	{
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					delete this->map[x][y][z];
				}

				this->map[x][y].clear();
			}

			this->map[x].clear();
		}
		
		this->map.clear();
	}

	void saveTileMap(std::string filename)
	{
		std::ofstream saveFile;
		saveFile.open(filename);

		if (saveFile.is_open())
		{
			saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";

			for (size_t x = 0; x < this->maxSize.x; x++)
			{
				for (size_t y = 0; y < this->maxSize.y; y++)
				{
					for (size_t z = 0; z < this->layers; z++)
					{
						saveFile << x << " " << y << " " << z << " " << this->map[x][y][z]->toString()
							<< "\n";
					}
				}
			}
		}
		else
		{
			std::cout << "Error: TileMap could not be saved to file '" << filename << "'" << std::endl;
		}

		saveFile.close();
	}

	void loadTileMap(std::string filename)
	{
		std::ifstream loadFile;
		loadFile.open(filename);

		if (loadFile.is_open())
		{
			bool colliding = false;
			loadFile >> maxSize.x >> maxSize.y >> gridSizeF >> layers;
			this->clear();
			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (size_t x = 0; x < this->maxSize.x; x++)
			{
				for (size_t y = 0; y < this->maxSize.y; y++)
				{
					this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

					for (size_t z = 0; z < this->layers; z++)
					{
						this->map[x][y].resize(this->layers, nullptr);
					}
				}
			}
			
			while (loadFile >> maxSize.x >> maxSize.y >> layers >> colliding)
			{
				std::cout << maxSize.x << ", " << maxSize.y << ", " << layers << "\n";
				this->map[maxSize.x][maxSize.y][layers] = new Tile(maxSize.x, maxSize.y, gridSizeF, colliding);
			}
		}
		else
		{
			std::cerr << "Error: TileMap could not load '" << filename << "'" << "\n";	
		}
		loadFile.close();
	}
};
ECS_DEFINE_TYPE(TileMap);
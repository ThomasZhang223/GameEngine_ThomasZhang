#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"

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
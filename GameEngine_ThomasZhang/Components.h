#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"

struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;
	float xSpeed, ySpeed;

	Transform(float x, float y)
	{
		xPos = x; 
		yPos = y;

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

	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider()
	{
		this->leftEdge = 0;
		this->rightEdge = 0;
		this->topEdge = 0;
		this->bottomEdge = 0;

		//std::memset(this, '\0', sizeof(BoxCollider));
	}

	void Update(float xSide, float ySide, float width, float height)
	{
		this->leftEdge = xSide;
		this->rightEdge = xSide + width;
		this->topEdge = ySide;
		this->bottomEdge = ySide + height;
	}
};
ECS_DEFINE_TYPE(BoxCollider);
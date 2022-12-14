#pragma once
#include <SDL_rect.h>
#include <math.h>
#include <string>
#include <utility>

class Player
{
public:
	enum PlayerSide {
		Left,
		Right,
	};

private:
	int score = 0;
	/*int x;
	int y;*/
	float speed;
	int screenHeight;
	int screenWidth;/*
	int myHeight = 80;
	int myWidth = 16;*/
	SDL_Rect myRect;
	PlayerSide mySide;


public:

	Player(int screenWidth, int screenHeight, PlayerSide myPosition);
	const SDL_Rect* getDestRect();
	std::string getScore();
	void moveUp();
	void moveDown();
	void upScore();
	PlayerSide getSide();
	int getYCenter();

	//deleting autogenerated constructors
	Player() = delete;
	Player(const Player&) = delete;
	Player(const Player&&) = delete;

};


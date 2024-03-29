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

private:
    int score = 0;
	float speed;
	int screenHeight;
    int screenWidth;
	SDL_Rect myRect;
	PlayerSide mySide;

};


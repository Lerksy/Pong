#include "Player.h"

Player::Player(int screenWidth, int screenHeight, PlayerSide myPosition) {
	this->speed = 35;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->mySide = myPosition;
	myRect.h = 80;
	myRect.w = 16;
	myRect.y = (screenHeight / 2) - (myRect.h / 2);
	//init my coords
	switch (this->mySide) {
	case Left: {
		myRect.x = static_cast<int>(this->screenWidth * 0.025 + myRect.w * 0.75);
		break;
	}
	case Right: {
		myRect.x = static_cast<int>(this->screenWidth * 0.975 - myRect.w * 1.75);
		break;
	}
	default: {
		myRect.x = 0;
	}
	}

}

const SDL_Rect* Player::getDestRect() {
	return &myRect;
}

std::string Player::getScore() {
	return std::to_string(score);
}

void Player::moveUp() {
	if (screenHeight * 0.025 + speed > myRect.y) {
		myRect.y = static_cast<int>(screenHeight * 0.025);
	}
	else {
		myRect.y -= static_cast<int>(speed);
	}
}

void Player::moveDown() {
	if ((screenHeight * 0.975 - myRect.h) - speed < myRect.y) {
		myRect.y = static_cast<int>(screenHeight * 0.975 - myRect.h);
	}
	else {
		myRect.y += static_cast<int>(speed);
	}
}

void Player::upScore() {
	score++;
}

Player::PlayerSide Player::getSide() {
	return mySide;
}

int Player::getYCenter() {
	return myRect.y + (myRect.h / 2);
}

#include "Player.h"

Player::Player(int screenWidth, int screenHeight, PlayerSide myPosition) {
	this->speed = 35;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->mySide = myPosition;
	this->y = (this->screenHeight / 2) - (myHeight / 2);
	//init my coords
	switch (this->mySide) {
	case Left: {
		this->x = static_cast<int>(this->screenWidth * 0.025 + this->myWidth * 0.75);
		break;
	}
	case Right: {
		this->x = static_cast<int>(this->screenWidth * 0.975 - this->myWidth * 1.75);
		break;
	}
	default: {
		this->x = 0;
	}
	}

}

SDL_Rect Player::getDestRect() {
	SDL_Rect ret;
	ret.h = myHeight;
	ret.w = myWidth;
	ret.x = static_cast<int>(this->x);
	ret.y = static_cast<int>(this->y);
	return ret;
}

std::string Player::getScore() {
	return std::to_string(score);
}

void Player::moveUp() {
	if (screenHeight * 0.025 + speed > y) {
		y = static_cast<int>(screenHeight * 0.025);
	}
	else {
		y -= static_cast<int>(speed);
	}
}

void Player::moveDown() {
	if ((screenHeight * 0.975 - myHeight) - speed < y) {
		y = static_cast<int>(screenHeight * 0.975 - myHeight);
	}
	else {
		y += static_cast<int>(speed);
	}
}

void Player::upScore() {
	score++;
}

Player::PlayerSide Player::getSide() {
	return mySide;
}

int Player::getYCenter() {
	return y + (myHeight / 2);
}

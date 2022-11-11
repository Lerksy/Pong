#include "Ball.h"

float Ball::pongAngle(int y1, int y2, int height) {
	return static_cast<float>((y1 + height / 2 - y2) / height / 2.0 * 3.1415 / 5.0);

}

Ball::Ball(int screenWidth, int screenHeight) {
	srand(static_cast<unsigned int>(time(0)));
	this->x = screenWidth / 2 - mySize / 2;
	this->y = screenHeight / 2 - mySize / 2;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->vx = static_cast<float>(rand() % 2 == 0 ? speed : -1 * speed);
	this->vy = static_cast<float>(-1 * (rand() % 8 + 1) / 10);
}

SDL_Rect Ball::getDestRect() {
	SDL_Rect ret;
	ret.h = mySize;
	ret.w = mySize;
	ret.x = this->x;
	ret.y = this->y;
	return ret;
}

void Ball::tick() {
	x += static_cast<int>(vx);
	y += static_cast<int>(vy);

	if (y < screenHeight * 0.025) {
		y = static_cast<int>(screenHeight * 0.025);
		vy *= -1;
	}

	if (y + mySize > screenHeight * 0.975) {
		y = static_cast<int>(screenHeight * 0.975 - mySize);
		vy *= -1;
	}

}

void Ball::reset()
{
	speed = initSpeed;
	this->x = screenWidth / 2 - mySize / 2;
	this->y = screenHeight / 2 - mySize / 2;
	this->vx = rand() % 2 == 0 ? speed : -1 * speed;
	this->vy = static_cast<float>(-1 * (rand() % 8 + 1) / 10);
}

void Ball::hitPlayer(Player* player) {
	SDL_Rect playerCoords = player->getDestRect();
	float angle = pongAngle(playerCoords.y, y, playerCoords.h);
	vy = static_cast<float>((vy > 0 ? -1 : 1) * speed * sin(angle));
	Player::PlayerSide playerSide = player->getSide();
	if (playerSide == Player::Left) {
		vx = static_cast<float>(speed * cos(angle));
		x = playerCoords.x + playerCoords.w + 1;
	}
	else if (playerSide == Player::Right) {
		vx = static_cast<float>(-1 * speed * cos(angle));
		x = playerCoords.x - mySize - 1;
	}
	if (speed + 1.0f >= maxSpeed) {
		speed = maxSpeed;
	}
	else {
		speed += 1.0f;
	}

}

int Ball::getYCenter() {
	return y + (mySize/2);
}

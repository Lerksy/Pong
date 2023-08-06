#include "Ball.h"

float Ball::pongAngle(float y1, float y2, int height) {
	return static_cast<float>((y1 + height / 2 - y2) / height / 2.0 * 3.1415 / 5.0);

}

Ball::Ball(int screenWidth, int screenHeight) {
	srand(time(0));
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	//reseting the ball position to default
	reset();
}

const SDL_Rect* Ball::getDestRect() {
	myRect.h = mySize;
	myRect.w = mySize;
	myRect.x = x;
	myRect.y = y;
	return &myRect;
}

void Ball::tick() {
	x += vx;
	y += vy;

	if (y < screenHeight * 0.025) {
		y = screenHeight * 0.025;
		vy *= -1;
	}

	if (y + mySize > screenHeight * 0.975) {
		y = screenHeight * 0.975 - mySize;
		vy *= -1;
	}

}

void Ball::reset()
{
	speed = initSpeed;
	this->x = screenWidth / 2 - mySize / 2;
	this->y = screenHeight / 2 - mySize / 2;
	this->vx = rand() % 2 == 0 ? speed : -1 * speed;
	this->vy = -0.5f;
}

void Ball::hitPlayer(Player* player) {
	SDL_Rect playerCoords = *(player->getDestRect());
	float angle = pongAngle(playerCoords.y, y, playerCoords.h);
	vy = (vy > 0 ? -1 : 1) * speed * sin(angle);
	Player::PlayerSide playerSide = player->getSide();
	if (playerSide == Player::Left) {
		vx = speed * cos(angle);
		x = playerCoords.x + playerCoords.w + 1;
	}
	else if (playerSide == Player::Right) {
		vx = -1 * speed * cos(angle);
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
	return y + (mySize / 2);
}

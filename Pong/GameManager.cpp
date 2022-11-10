#include "GameManager.h"


//game methods

void GameManager::processEvents(SDL_Event* event) {
	switch (event->type)
	{
	case SDL_QUIT: {
		game->kill();
		break;
	}
	case SDL_KEYDOWN: {
		SDL_Keysym keyPressed = event->key.keysym;
		switch (keyPressed.scancode) {
		case 82: {
			rightPlayer->moveUp();
			break;
		}
		case 81: {
			rightPlayer->moveDown();
			break;
		}
		case 26: {
			leftPlayer->moveUp();
			break;
		}
		case 22: {
			leftPlayer->moveDown();
			break;
		}
		}
		break;
	}
	default:
		break;
	}
	delete event;
}

void GameManager::updateObjects() {
	ball->tick();

	//checking hits with players
	if (SDL_HasIntersection(&ball->getDestRect(), &leftPlayer->getDestRect())) {
		ball->hitPlayer(leftPlayer);
	}
	else if (SDL_HasIntersection(&ball->getDestRect(), &rightPlayer->getDestRect())) {
		ball->hitPlayer(rightPlayer);
	}

	//checking hits with deadzones
	if (SDL_HasIntersection(&ball->getDestRect(), &leftDeadzone)) {
		rightPlayer->upScore();
		ball->reset();
	}
	else if (SDL_HasIntersection(&ball->getDestRect(), &rightDeadzone)) {
		leftPlayer->upScore();
		ball->reset();
	}


}

GameManager::GameManager(int width, int height, int FPS) {
	this->width = width;
	this->height = height;
	this->FPS = FPS;
	this->leftPlayer = new Player(width, height, Player::Left);
	this->rightPlayer = new Player(width, height, Player::Right);
	this->ball = new Ball(width, height);
	game = new SDLScene(this->width, this->height, leftPlayer, rightPlayer, ball);
	game->init();
	leftDeadzone = { 0, 0, static_cast<int>(width * 0.025), height };
	rightDeadzone = { static_cast<int>(width * 0.975), 0, static_cast<int>(width * 0.025), height };
}

void GameManager::run()
{
	int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (game->isRunning()) {

		frameStart = SDL_GetTicks();

		processEvents(game->getEvents());
		updateObjects();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();
	delete leftPlayer;
	delete rightPlayer;
	delete ball;
	delete game;
}

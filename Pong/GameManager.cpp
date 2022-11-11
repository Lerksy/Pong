#include "GameManager.h"


//game methods

void GameManager::processEvents(SDL_Event* event) {

	if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE) {
		game->kill();
		return;
	}

	//distributing event proceed
	switch (state)
	{
	case MainMenu:
		processMenuEvents(event);
		break;
	case GameVSBot:
		processGameEvents(event);
		break;
	case GameVsPlayer:
		processGameEvents(event);
		break;
	case GameOver:
		break;
	default:
		break;
	}

	delete event;
}

void GameManager::processMenuEvents(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN: {
		SDL_MouseButtonEvent mouseClick = event->button;
		if (mouseClick.button != SDL_BUTTON_LEFT) break;
		if (checkIsMouseClickedOnButton(mouseClick.x, mouseClick.y, game->getStartVsBotButtonRect())) {
			state = GameState::GameVSBot;
		}
		else if (checkIsMouseClickedOnButton(mouseClick.x, mouseClick.y, game->getStartVsPlayerButtonRect())) {
			state = GameState::GameVsPlayer;
		}
		break;
	}
	default:
		break;
	}
}

void GameManager::processGameEvents(SDL_Event* event)
{
	switch (event->type)
	{
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
			if (state == GameState::GameVsPlayer) leftPlayer->moveUp();
			break;
		}
		case 22: {
			if (state == GameState::GameVsPlayer) leftPlayer->moveDown();
			break;
		}
		}
		break;
	}
	default:
		break;
	}
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

	//simple bot AI (cheat mode is off :D)
	if (state == GameState::GameVSBot) {
		if ((botTicks++) > FPS) {
			botTicks = 0;
			int bc = ball->getYCenter();
			int pc = leftPlayer->getYCenter();
			if (ball->getYCenter() < leftPlayer->getYCenter()) leftPlayer->moveUp();
			else if (ball->getYCenter() > leftPlayer->getYCenter()) leftPlayer->moveDown();
		}
	}

	//checking scores, who first got 11 points - that won!
	if (stoi(leftPlayer->getScore()) > 10 || stoi(rightPlayer->getScore()) > 10) {
		state = GameState::GameOver;
	}

}

//service methods

bool GameManager::checkIsMouseClickedOnButton(int mouseX, int mouseY, SDL_Rect btnZone) {
	if (mouseX >= btnZone.x &&
		mouseX <= (btnZone.x + btnZone.w) &&
		mouseY >= btnZone.y &&
		mouseY <= (btnZone.y + btnZone.h)) {
		return true;
	}
	return false;
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

		if (state == GameState::MainMenu) {
			game->renderMainMenu();
		}

		if (state == GameState::GameVsPlayer || state == GameState::GameVSBot) {
			updateObjects();
			game->renderGame();
		}
		if (state == GameState::GameOver) {
			game->renderGameOver();
		}
		//limiting FPS
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

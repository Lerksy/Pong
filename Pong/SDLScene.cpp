#include "SDLScene.h"

SDLScene::SDLScene(int width, int height, Player * leftPlayer, Player * rightPlayer, Ball* ball) {
	this->SCENE_WIDTH = width;
	this->SCENE_HEIGHT = height;
	this->leftPlayer = leftPlayer;
	this->rightPlayer = rightPlayer;
	this->ball = ball;
}

void SDLScene::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL Init failed %s", SDL_GetError());
		exit(1);
	}
	//init window
	window = SDL_CreateWindow("Pong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCENE_WIDTH, SCENE_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Log("SDL Window creation failed %s", SDL_GetError());
		exit(1);
	}
	//init renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		SDL_Log("SDL Renderer creation failed %s", SDL_GetError());
		exit(1);
	}
	//init font library
	if (TTF_Init() != 0) {
		SDL_Log("SDL TTF init failed %s", SDL_GetError);
		exit(1);
	}
	//setup basics
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	active = true;
	textures = new TextureLoader(renderer);

	//setting up some texture zones
	//reminder: start x, start y, width of block, height of block;
	leftCounterZone = {
		static_cast<int>(SCENE_WIDTH * 0.03),
		static_cast<int>(SCENE_HEIGHT * 0.03),
		static_cast<int>(SCENE_WIDTH * 0.1),
		static_cast<int>(SCENE_HEIGHT * 0.15)
	};
	rightCounterZone = {
		static_cast<int>(SCENE_WIDTH * 0.87),
		static_cast<int>(SCENE_HEIGHT * 0.03),
		static_cast<int>(SCENE_WIDTH * 0.1),
		static_cast<int>(SCENE_HEIGHT * 0.15)
	};
	startVSBotButtonZone = {
		static_cast<int>(SCENE_WIDTH * 0.26),
		static_cast<int>(SCENE_HEIGHT * 0.27),
		static_cast<int>(SCENE_WIDTH * 0.46),
		static_cast<int>(SCENE_HEIGHT * 0.2)
	};
	startVSPlayerButtonZone = {
		static_cast<int>(SCENE_WIDTH * 0.26),
		static_cast<int>(SCENE_HEIGHT * 0.52),
		static_cast<int>(SCENE_WIDTH * 0.46),
		static_cast<int>(SCENE_HEIGHT * 0.2)
	};
}

bool SDLScene::isRunning() { return active; }

SDL_Event* SDLScene::getEvents()
{
	SDL_Event *event = new SDL_Event;
	SDL_PollEvent(event);
	return event;
}

void SDLScene::renderMainMenu()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures->getTexture("background"), nullptr, nullptr);
	SDL_RenderCopy(renderer, textures->getTexture("startbotbutton"), nullptr, &startVSBotButtonZone);
	SDL_RenderCopy(renderer, textures->getTexture("startplayerbutton"), nullptr, &startVSPlayerButtonZone);
	SDL_RenderPresent(renderer);
}

void SDLScene::renderGame()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures->getTexture("background"), nullptr, nullptr);
	SDL_RenderCopy(renderer, textures->renderText(leftPlayer->getScore()), nullptr, &leftCounterZone);
	SDL_RenderCopy(renderer, textures->renderText(rightPlayer->getScore()), nullptr, &rightCounterZone);
	SDL_RenderCopy(renderer, textures->getTexture("platform"), nullptr, &leftPlayer->getDestRect());
	SDL_RenderCopy(renderer, textures->getTexture("platform"), nullptr, &rightPlayer->getDestRect());
	SDL_RenderCopy(renderer, textures->getTexture("ball"), nullptr, &ball->getDestRect());
	SDL_RenderPresent(renderer);
}

void SDLScene::renderGameOver()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures->getTexture("background"), nullptr, nullptr);
	SDL_RenderCopy(renderer, textures->renderText(leftPlayer->getScore()), nullptr, &leftCounterZone);
	SDL_RenderCopy(renderer, textures->renderText(rightPlayer->getScore()), nullptr, &rightCounterZone);
	SDL_RenderCopy(renderer, textures->renderText("Game Over"), nullptr, &startVSPlayerButtonZone);
	SDL_RenderPresent(renderer);
}

void SDLScene::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDLScene::kill() {
	active = false;
}

//some getters for our Parent

SDL_Rect SDLScene::getStartVsBotButtonRect() { return startVSBotButtonZone; }

SDL_Rect SDLScene::getStartVsPlayerButtonRect() { return startVSPlayerButtonZone; }

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string>
#include "Player.h"
#include "Ball.h"
#include "TextureLoader.h"

class SDLScene
{
	// SDL constants
	int SCENE_WIDTH;
	int SCENE_HEIGHT;

	//SDL vars
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Textures
	TextureLoader* textures = nullptr;

	//counter zones
	SDL_Rect rightCounterZone;
	SDL_Rect leftCounterZone;

	//Main menu vars
	SDL_Rect startVSPlayerButtonZone;
	SDL_Rect startVSBotButtonZone;

	//Custom vars
	bool active = false;
	Player* leftPlayer = nullptr;
	Player* rightPlayer = nullptr;
	Ball* ball = nullptr;

public:
	SDLScene(int width, int height, Player* leftPlayer, Player* rightPlayer, Ball* ball);
	void init();
	bool isRunning();
	SDL_Event* getEvents();
	void renderMainMenu();
	void renderGame();
	void renderGameOver();
	void clean();
	void kill();

	//some getters for our Parent
	SDL_Rect getStartVsBotButtonRect();
	SDL_Rect getStartVsPlayerButtonRect();

	//deleting autogenerated constructors
	SDLScene() = delete;
	SDLScene(SDLScene&) = delete;
	SDLScene(SDLScene&&) = delete;
};


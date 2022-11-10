#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
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

	//Custom vars
	bool active = false;
	Player* leftPlayer = nullptr;
	Player* rightPlayer = nullptr;
	Ball* ball = nullptr;

public:
	SDLScene(int width, int height, Player * leftPlayer, Player * rightPlayer, Ball* ball);
	SDLScene() = delete;
	SDLScene(SDLScene&) = delete;
	SDLScene(SDLScene&&) = delete;
	void init();
	bool isRunning();
	SDL_Event* getEvents();
	void render();
	void clean();
	void kill();
};


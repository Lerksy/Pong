#pragma once
#include <SDL.h>
#include "Player.h"
#include "SDLScene.h"
#include "Ball.h"
#include "GameState.h"

class GameManager
{
	//Field Objects
	Player* leftPlayer;
	Player* rightPlayer;
	Ball* ball;

	//Scene
	SDLScene* game = nullptr;

	//Deadzone hitboxes
	SDL_Rect leftDeadzone;
	SDL_Rect rightDeadzone;


	//Game Vars
	int height;
	int width;
	int FPS;
	GameState state = MainMenu;
	int botTicks = 0;

	//game methods
	void processEvents(SDL_Event* event);
	void processMenuEvents(SDL_Event* event);
	void processGameEvents(SDL_Event* event);
	void updateObjects();

	//service methods
	bool checkIsMouseClickedOnButton(int mouseX, int mouseY, SDL_Rect btnZone);


public:
	GameManager(int width, int height, int FPS);
	void run();


	//deleting autogenerated constructors
	GameManager() = delete;
	GameManager(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
};

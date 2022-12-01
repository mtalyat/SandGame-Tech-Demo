#include "EngineData.h"
#include <iostream>

EngineData::EngineData()
	: isRunning(false), lastMouseX(0), lastMouseY(0), mouseX(0), mouseY(0), isMouseDown(false), mouseButton(-1), isPaused(false), shouldReset(false)
{
	SDL_Init(SDL_INIT_VIDEO);

	//window
	window = SDL_CreateWindow("Sand Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, 0);

	if (window == nullptr)
	{
		std::cout << "Window null: " << SDL_GetError() << std::endl;
	}

	//renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr)
	{
		std::cout << "Renderer null: " << SDL_GetError() << std::endl;
	}
}

EngineData::~EngineData()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void EngineData::setMousePos(int const x, int const y)
{
	if (!isMouseDown)
	{
		//mouse is not down
		lastMouseX = x;
		mouseX = x;
		lastMouseY = y;
		mouseY = y;
	}
	else {
		//mouse has been down
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		mouseX = x;
		mouseY = y;
	}
}

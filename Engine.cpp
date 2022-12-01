#include "Engine.h"
#include <iostream>
#include <thread>
#include "Matrix.h"
#include "Stopwatch.h"
#include "Time.h"
#include "Random.h"

//elements
#include "Sand.h"
#include "Water.h"
#include "Stone.h"
#include "Wood.h"
#include "Molten.h"
#include "Steam.h"
#include "Rock.h"
#include "Glass.h"
#include "Ice.h"
#include "Flame.h"
#include "Iron.h";
#include "Spark.h"

void Engine::handleEvents(SDL_Event& const event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		data.isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
	{
		data.isMouseDown = true;
		data.mouseButton = event.button.button - 1;
	}
	break;
	case SDL_MOUSEBUTTONUP:
	{
		data.isMouseDown = false;
		data.mouseButton = -1;
	}
	break;
	case SDL_MOUSEWHEEL:
	{
		if (event.wheel.y > 0)
		{
			//scroll up
			brushSize += event.wheel.y;
		}
		else if (event.wheel.y < 0)
		{
			//scroll down
			brushSize = std::max(1, brushSize + event.wheel.y);
		}
	}
	break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_R:
			data.shouldReset = true;
			break;
		case SDL_SCANCODE_SPACE:
			data.isPaused = !data.isPaused;
			break;
		}
	break;
	}
}

Engine::Engine()
{
	random_seed_time();
}

Engine::~Engine()
{

}

void Engine::run()
{
	SDL_Event event;
	SDL_Renderer* renderer = data.getRenderer();
	data.isRunning = true;

	int const mouseScale = 16;

	Matrix matrix(1024 / mouseScale, 1024 / mouseScale, renderer);

	//for rendering to a location on the screen
	//SDL_Rect dstrect = { 100, 100, 128, 128 };

	int elementType = 0;

	Stopwatch watch;
	watch.start();

	float FPStimer = 0.0f;
	int frameCount = 0;

	int const FPScap = 60;
	float const FPScapTime = 1.0f / FPScap;

	while (data.isRunning)
	{
		//get events from window
		//SDL_WaitEvent(&event);
		while (SDL_PollEvent(&event)) {
			//handle events
			handleEvents(event);
		}

		if (data.shouldReset)
		{
			data.shouldReset = false;
			matrix.clear();
		}

		//get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		data.setMousePos(x, y);

		Element * debugElement = matrix.getElement(data.mouseX / mouseScale, data.mouseY / mouseScale);
		if (debugElement)
		{
			std::cout << "[" << debugElement->toString().c_str() << "] " << debugElement->getTemperature() << "/" << debugElement->getBaseTemperature() << std::endl;
		}

		//TEMP INPUT
		Uint8 const* keys = SDL_GetKeyboardState(NULL);

		for (int i = 0; i < 10; i++)
		{
			if (keys[SDL_SCANCODE_1 + i])
			{
				elementType = i;
				break;
			}
		}

		if (data.isMouseDown)
		{
			int lastX = data.lastMouseX / mouseScale;
			int lastY = data.lastMouseY / mouseScale;
			int x = data.mouseX / mouseScale;
			int y = data.mouseY / mouseScale;

			if (data.mouseButton == 0)
			{
				switch (elementType)
				{
				case 0:
					matrix.trySetElements<Sand>(lastX, lastY, x, y, brushSize);
					break;
				case 1:
					matrix.trySetElements<Water>(lastX, lastY, x, y, brushSize);
					break;
				case 2:
					matrix.trySetElements<Molten>(lastX, lastY, x, y, brushSize);
					break;
				case 3:
					matrix.trySetElements<Wood>(lastX, lastY, x, y, brushSize);
					break;
				case 4:
					matrix.trySetElements<Iron>(lastX, lastY, x, y, brushSize);
					break;
				case 5:
					matrix.trySetElements<Spark>(lastX, lastY, x, y, brushSize);
					break;
				case 6:
					matrix.trySetElements<Rock>(lastX, lastY, x, y, brushSize);
					break;
				case 7:
					matrix.trySetElements<Glass>(lastX, lastY, x, y, brushSize);
					break;
				case 8:
					matrix.trySetElements<Ice>(lastX, lastY, x, y, brushSize);
					break;
				case 9:
					matrix.trySetElements<Flame>(lastX, lastY, x, y, brushSize);
					break;
				}
			}
			else if (data.mouseButton == 2)
			{
				matrix.destroyElements(x, y, brushSize);
				matrix.activateSurrounding(x, y, brushSize);
			}

		}

		//update
		if (!data.isPaused)
		{
			matrix.updateAll();
		}

		//render
		matrix.updateTexture();

		//SDL_RenderCopy(renderer, texture, nullptr, &dstrect);//render to location
		SDL_RenderCopy(renderer, matrix.getTexture(), nullptr, nullptr);
		SDL_RenderPresent(renderer);

		while (watch.getTimeSinceLastLap() < FPScapTime)
		{
			continue;
		}

		//get time passed this frame
		watch.lap();
		Time::deltaTime = watch.getLapTimeElapsed();
		FPStimer += Time::deltaTime;
		Time::totalTime = watch.getTotalTimeElapsed();

		frameCount++;

		if (FPStimer >= 1.0f)
		{
			while (FPStimer >= 1.0f)
			{
				FPStimer -= 1.0f;
			}

			std::cout << "FPS: " << frameCount << ", deltaTime: " << Time::deltaTime << std::endl;

			frameCount = 0;
		}
	}

	watch.stop();

	std::cout << "Program ran for " << watch.getTotalTimeElapsed() << " seconds." << std::endl;
}

void Engine::quit()
{
	data.isRunning = false;
}

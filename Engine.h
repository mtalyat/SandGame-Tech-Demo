#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "Object.h"
#include "EngineData.h"

class Engine :
    public Object
{
private:
    EngineData data;
    int brushSize = 1;

private:
    void handleEvents(SDL_Event& const event);

public:
    Engine();
    ~Engine();

    void run();

    void quit();
};

#endif
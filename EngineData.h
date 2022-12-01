#ifndef ENGINEDATA_H
#define ENGINEDATA_H

#include "Object.h"
#include "Matrix.h"

class EngineData :
    public Object
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    bool isRunning;

    int lastMouseX, lastMouseY;
    int mouseX, mouseY;
    bool isMouseDown;
    int mouseButton;

    bool isPaused;
    bool shouldReset;

private:


public:
    EngineData();
    ~EngineData();

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }

    void setMousePos(int const x, int const y);
};

#endif

#pragma once
#include <string>
#include <SDL2\SDL.h>
#include "Transform.h"

class Display {
public:

	Display(int width, int height, const std::string& windowTitle);
	virtual ~Display();

	void windowClear(float r, float g, float b, float a);
	bool windowUpdate(int& x, int& y, Transform& pending, int& projectionMode, unsigned int& dataBaseMode);
	bool isClosed();
private:
	bool windowClosed;
	SDL_Window* myWindow;
	SDL_GLContext myContext;
};
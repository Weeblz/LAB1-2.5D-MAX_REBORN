#include "Display.h"
#include <iostream>
#include <GL\glew.h>
#include <AntTweakBar.h>

Display::Display(int width, int height, const std::string& windowTitle) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	myWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	myContext = SDL_GL_CreateContext(myWindow);

	if (glewInit()) {
		std::cerr << "Glew isn't initialized" << std::endl;
	}

	windowClosed = false;
}

Display::~Display() {
	SDL_GL_DeleteContext(myContext);
	SDL_DestroyWindow(myWindow);
	SDL_Quit();
}

void Display::windowUpdate() {
	SDL_GL_SwapWindow(myWindow);

	int handled;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		handled = TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

		if (!handled) {
			if (event.type == SDL_QUIT) {
				windowClosed = true;
			}
		}
	}

}

bool Display::isClosed() {
	return windowClosed;
}

void Display::windowClear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
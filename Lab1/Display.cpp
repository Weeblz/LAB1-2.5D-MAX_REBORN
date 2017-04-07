#include "Display.h"
#include "Bar.h"
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
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

	myWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	myContext = SDL_GL_CreateContext(myWindow);

	if (glewInit()) {
		std::cerr << "Glew isn't initialized" << std::endl;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	windowClosed = false;
}

Display::~Display() {
	SDL_GL_DeleteContext(myContext);
	SDL_DestroyWindow(myWindow);
	SDL_Quit();
}

bool Display::windowUpdate(int& x, int& y, Transform& pending, int& projectionMode, bool& saveScene) {
 	SDL_GL_SwapWindow(myWindow);

	bool changeColor = false;
	x = -1;		// if no click registred x and y are -1
	y = -1;

	GLuint index;
	int handled;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		handled = TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

		if (!handled) {
			switch (event.type) {
				case SDL_QUIT:
					windowClosed = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x, &y);
					glReadPixels(x, 600 - y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
					if (index) {
						objects[index - 1].updateActive();
						std::cout << index << std::endl;
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							pending.incrY();
							break;
						case SDLK_DOWN:
							pending.decrY();
							break;
						case SDLK_LEFT:
							pending.decrX();
							break;
						case SDLK_RIGHT:
							pending.incrX();
							break;
						case SDLK_f:			// "f" is for "FAR"
							pending.decrZ();
							break;
						case SDLK_n:			// "n" is for "NEAR"
							pending.incrZ();
							break;
						case SDLK_x:		    // turning active figure around it's "x" axis (not quite visible for ellipsoids)
							pending.turnX();
							break;
						case SDLK_y:			// turning active figure around it's "y" axis
							pending.turnY();
							break;
						case SDLK_z:			// turning active figure around it's "z" axis
							pending.turnZ();
							break;
						case SDLK_s:
							pending.shrink();
							break;
						case SDLK_e:
							pending.expand();
							break;
						case SDLK_c:			// changing "c"olor for active objects
							changeColor = true;
							break;
						case SDLK_0:
							projectionMode = NO_PROJECTIONS; // turn off projections
							break;
						case SDLK_1:
							projectionMode = X_PROJECTION;	 // show x projection [only]
							break;
						case SDLK_2:
							projectionMode = Y_PROJECTION;	 // show y projection [only]
							break;
						case SDLK_3:
							projectionMode = Z_PROJECTION;	 // show z projection [only]
							break;
						case SDLK_F1:
							saveScene = true;
							break;
					}
			}
		}
	}
	return changeColor;
}

bool Display::isClosed() {
	return windowClosed;
}

void Display::windowClear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearStencil(0);
}
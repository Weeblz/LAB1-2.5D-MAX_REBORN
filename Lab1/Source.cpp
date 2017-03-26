#include <iostream>
#include "Display.h"
#include "Shader.h"

int main(int argc, char** argv) {
	Display workingArea(800, 600, "Random Title");

	Shader shader("basicShader");

	while (!workingArea.isClosed()) {
		workingArea.windowClear(0.0f, 0.5f, 0.5f, 1.0f);
		shader.bind();
		workingArea.windowUpdate();
	}
	return 0;
}
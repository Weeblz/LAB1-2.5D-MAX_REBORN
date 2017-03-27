#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"

int main(int argc, char** argv) {
	Display workingArea(800, 600, "Random Title");
	Shader shader("basicShader");
	Transform tr;

	Vertex vertices[] = { Vertex(glm::vec3(0.0, 1.0, 0.0)),
						  Vertex(glm::vec3(-1.0, -1.0, 0.0)),
						  Vertex(glm::vec3(1.0, -1.0, 0.0))
	};
	Mesh mesh(vertices, 3);

	while (!workingArea.isClosed()) {
		workingArea.windowClear(0.0f, 0.5f, 0.5f, 1.0f);
		shader.bind();

		mesh.draw();
		workingArea.windowUpdate();
	}
	return 0;
}
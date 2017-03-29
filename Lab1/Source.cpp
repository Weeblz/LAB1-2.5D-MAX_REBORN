#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

int main(int argc, char** argv) {
	Display workingArea(800, 600, "Random Title");
	Shader shader("basicShader");
	Camera camera(glm::vec3(-2, 2, -10), 70.0f, (float)800 / (float)600, 0.01f, 1000.0f);
	Transform tr;

	Vertex vertices[] = { Vertex(glm::vec3(0.0, 1.0, 0.0)),
						  Vertex(glm::vec3(-1.0, -1.0, 0.0)),
						  Vertex(glm::vec3(1.0, -1.0, 0.0))
	};

	Vertex Xaxis[] = { Vertex(glm::vec3(-100.0, 0.0, 0.0)), Vertex(glm::vec3(100.0, 0.0, 0.0)) };  //x axis
	Vertex Yaxis[] = { Vertex(glm::vec3(0.0, -100.0, 0.0)), Vertex(glm::vec3(0.0, 100.0, 0.0)) };  //y axis
	Vertex Zaxis[] = { Vertex(glm::vec3(0.0, 0.0, -100.0)), Vertex(glm::vec3(0.0, 0.0, 100.0)) };  //z axis

	Mesh X(Xaxis, 2), Y(Yaxis, 2), Z(Zaxis, 2), mesh(vertices, 3);

	int cnt = 0;

	glPolygonMode(GL_FRONT, GL_LINE);

	while (!workingArea.isClosed()) {
		workingArea.windowClear(0.0f, 0.0f, 0.0f, 1.0f);
		shader.bind();

		X.draw(GL_LINES);
		Y.draw(GL_LINES);
		Z.draw(GL_LINES);

		tr.setScale({2, 2, 2});
		shader.update(tr, camera);
		mesh.draw(GL_TRIANGLES);

		workingArea.windowUpdate();

		cnt++;
	}
	return 0;
}
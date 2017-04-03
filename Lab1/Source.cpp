#include <iostream>
#include <vector>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Figure.h"
#include "Bar.h"

int main(int argc, char** argv) {
	Display workingArea(800, 600, "Random Title");
	Shader shader("basicShader");
	Camera camera(glm::vec3(-2, 2, -10), 70.0f, (float)800 / (float)600, 0.01f, 1000.0f);
	Transform Dynamic, None;

	Bar bar(800, 600, "ATB");

	Vertex Xaxis[] = { Vertex(glm::vec3(-100.0, 0.0, 0.0)), Vertex(glm::vec3(100.0, 0.0, 0.0)) };  //x axis
	Vertex Yaxis[] = { Vertex(glm::vec3(0.0, -100.0, 0.0)), Vertex(glm::vec3(0.0, 100.0, 0.0)) };  //y axis
	Vertex Zaxis[] = { Vertex(glm::vec3(0.0, 0.0, -100.0)), Vertex(glm::vec3(0.0, 0.0, 100.0)) };  //z axis

	Mesh X(Xaxis, 2), Y(Yaxis, 2), Z(Zaxis, 2);
	Mesh ellipsoid("res/ellipsoid.obj");
	Mesh cuboid("res/cuboid.obj");

	glPolygonMode(GL_FRONT, GL_LINE);
	
	while (!workingArea.isClosed()) {
		workingArea.windowClear(0.5f, 0.5f, 0.5f, 1.0f);
		shader.bind();

		shader.update(None, camera);
		X.draw(GL_LINES);
		Y.draw(GL_LINES);
		Z.draw(GL_LINES);

		for (int i = 0; i < objects.size(); i++) {
			shader.update(objects[i].getTransformation(), camera);
			objects[i].getType() == Ellipsoid ? ellipsoid.draw(GL_TRIANGLES) : cuboid.draw(GL_TRIANGLES);
		}
		//cuboid.draw(GL_TRIANGLES);

		//Dynamic.setScale({2, 2, 2});
		//shader.update(Dynamic, camera);

		TwDraw();

		workingArea.windowUpdate();
	}
	return 0;
}
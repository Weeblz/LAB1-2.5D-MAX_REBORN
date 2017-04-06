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
	Camera camera(glm::vec3(2, 2, 10), 70.0f, (float)800 / (float)600, 0.01f, 1000.0f);
	Transform Dynamic, None;
	bool changeColor = false;		//do we need to get new colors for active objects or not
	int mode = 0;					//object projections mode. See defines in Figure.h
	int xClick = -1, yClick = -1;	//storing clicks coordinates

	Bar bar(800, 600, "ATB");

	Vertex Xaxis[] = { Vertex(glm::vec3(-100.0, 0.0, 0.0)), Vertex(glm::vec3(100.0, 0.0, 0.0)) };  //x axis
	Vertex Yaxis[] = { Vertex(glm::vec3(0.0, -100.0, 0.0)), Vertex(glm::vec3(0.0, 100.0, 0.0)) };  //y axis
	Vertex Zaxis[] = { Vertex(glm::vec3(0.0, 0.0, -100.0)), Vertex(glm::vec3(0.0, 0.0, 100.0)) };  //z axis

	Mesh X(Xaxis, 2), Y(Yaxis, 2), Z(Zaxis, 2);
	Mesh ellipsoid("res/ellipsoid.obj");
	Mesh cuboid("res/cuboid.obj");

	while (!workingArea.isClosed()) {
		workingArea.windowClear(0.5f, 0.5f, 0.5f, 1.0f);
		shader.bind();

		shader.update(None, camera, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), NO_PROJECTIONS);
		glStencilFunc(GL_ALWAYS, 0, -1);
		X.draw(GL_LINES);
		Y.draw(GL_LINES);
		Z.draw(GL_LINES);

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i].isActive()) {
				objects[i].updateState(Dynamic);
				if (changeColor) {
					objects[i].updateColor();
				}
				if (mode) {
					shader.update(objects[i].getTransformation(), camera, objects[i].getColor(), mode);
					glStencilFunc(GL_ALWAYS, 0, -1);
					objects[i].getType() == Ellipsoid ? ellipsoid.draw(GL_TRIANGLES) : cuboid.draw(GL_TRIANGLES);
				}
			}
			shader.update(objects[i].getTransformation(), camera, objects[i].getColor(), NO_PROJECTIONS);
			glStencilFunc(GL_ALWAYS, i + 1, -1);
			objects[i].getType() == Ellipsoid ? ellipsoid.draw(GL_TRIANGLES) : cuboid.draw(GL_TRIANGLES);
		}

		TwDraw();

		Dynamic.reset();
		changeColor = workingArea.windowUpdate(xClick, yClick, Dynamic, mode);
	}
	return 0;
}
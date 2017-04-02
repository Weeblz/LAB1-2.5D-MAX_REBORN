#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

enum figureType { Cuboid, Ellipsoid };

class Figure {
public:
	Figure(figureType essence, double x, double y, double z) {
		this->essence = essence;
		transformation = glm::scale(glm::vec3(x, y, z));
		color = glm::vec4({ 1.0, 0.0, 0.0, 1.0 });
		active = true;
	}

	void updateState(glm::mat4 transform) {
		transformation = transform * transformation;
	}
	void updateState(glm::vec4 newColor) {
		color = newColor;
	}
private:
	figureType essence;
	glm::mat4 transformation;
	glm::vec4 color;
	bool active;
};

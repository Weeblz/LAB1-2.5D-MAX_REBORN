#pragma once
#include <glm\glm.hpp>

enum figureType { Cuboid, Ellipsoid };

class Figure {
	Figure(figureType essence) {
		this->essence = essence;
		transformation = glm::mat4({ 1.0, 0.0, 0.0, 0.0,
									 0.0, 1.0, 0.0, 0.0,
									 0.0, 0.0, 1.0, 0.0,
									 0.0, 0.0, 0.0, 1.0 });
	}

	void updateState(glm::mat4 transform) {
		transformation = transform * transformation;
	}
private:
	figureType essence;
	glm::mat4 transformation;
};

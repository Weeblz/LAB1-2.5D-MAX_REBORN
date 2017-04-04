#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Transform.h"

enum figureType { Cuboid, Ellipsoid };

class Figure {
public:
	Figure(figureType essence, double x, double y, double z) {
		this->essence = essence;
		transformation = Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(x, y, z));
		color = glm::vec4({ 1.0, 0.0, 0.0, 1.0 });
		active = true;
	}

	void updateState(Transform transform) {
		transformation = transform + transformation;
	}
	void updateState(glm::vec4 newColor) {
		color = newColor;
	}
	void updateActive() { active = !active; }

	bool isActive() { return active; }

	Transform getTransformation() { return transformation; }
	figureType getType() { return essence; }

private:
	figureType essence;
	Transform transformation;
	glm::vec4 color;
	bool active;
};

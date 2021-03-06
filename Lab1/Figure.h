#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <cstdlib>
#include <ctime>
#include "Transform.h"

#define NO_PROJECTIONS 0
#define X_PROJECTION 1
#define Y_PROJECTION 2
#define Z_PROJECTION 3

enum figureType { Cuboid, Ellipsoid };

class Figure {
public:
	Figure(figureType essence, double x, double y, double z) {
		srand(static_cast <unsigned> (time(0)));
		this->essence = essence;
		transformation = Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(x, y, z));
		color = glm::vec4({ static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
							static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
							static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 });

		active = true;
	}

	Figure(figureType essence, bool isActive, glm::vec4 color, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->essence = essence;
		active = isActive;
		transformation = Transform(position, rotation, scale);
		this->color = color;
	}

	void updateState(Transform transform) {
		transformation = transform + transformation;
	}
	void updateColor() {
		color = glm::vec4({ static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
							static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
							static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 });
	}
	void updateActive() { active = !active; }

	bool isActive() { return active; }
	glm::vec4 getColor() { return color; }
	Transform getTransformation() { return transformation; }
	figureType getType() { return essence; }

private:
	figureType essence;
	Transform transformation;
	glm::vec4 color;
	bool active;
};

#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& pos, float field, float aspect, float zNear, float zFar) {
		perspective = glm::perspective(field, aspect, zNear, zFar);
		position = pos;
		forwardDir = glm::vec3(0, 0, -1);
		upDir = glm::vec3(0, 1, 0);
	}

	void setPosition(glm::vec3 pos) {
		position = pos;
	}

	glm::mat4 getViewProjecion() const {
		return perspective * glm::lookAt(position, position + forwardDir, upDir);
	}
private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forwardDir;
	glm::vec3 upDir;
};
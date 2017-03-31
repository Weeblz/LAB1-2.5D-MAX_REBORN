#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform {
public:
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	glm::mat4 getModel() const {
		glm::mat4 posMatrix = glm::translate(position);
		glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 scaleMatrix = glm::scale(scale);

		glm::mat4 rotationMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotationMatrix * scaleMatrix;
	}

	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getScale() { return scale; }

	void setPosition(glm::vec3 pos) { position = pos; }
	void setRotation(glm::vec3 rot) { rotation = rot; }
	void setScale(glm::vec3 sc) { scale = sc; }

	void reset() {
		position = glm::vec3();
		rotation = glm::vec3();
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
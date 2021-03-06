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

	void incrX() { position += glm::vec3(0.1f, 0.0f, 0.0f); }
	void incrY() { position += glm::vec3(0.0f, 0.1f, 0.0f); }
	void incrZ() { position += glm::vec3(0.0f, 0.0f, 0.1f); }

	void decrX() { position -= glm::vec3(0.1f, 0.0f, 0.0f); }
	void decrY() { position -= glm::vec3(0.0f, 0.1f, 0.0f); }
	void decrZ() { position -= glm::vec3(0.0f, 0.0f, 0.1f); }

	void turnX() { rotation += glm::vec3(0.1f, 0.0f, 0.0f); }
	void turnY() { rotation += glm::vec3(0.0f, 0.1f, 0.0f); }
	void turnZ() { rotation += glm::vec3(0.0f, 0.0f, 0.1f); }

	void shrink() { scale /= glm::vec3(1.1f, 1.1f, 1.1f); }
	void expand() { scale *= glm::vec3(1.1f, 1.1f, 1.1f); }

	void reset() {
		position = glm::vec3();
		rotation = glm::vec3();
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	const Transform operator + (const Transform& a) {
		Transform result(*this);
		result.position = this->position + a.position;
		result.rotation = this->rotation + a.rotation;
		result.scale = this->scale * a.scale;
		return result;
	}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
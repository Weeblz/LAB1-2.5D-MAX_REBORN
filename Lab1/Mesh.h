#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex {
public:
	Vertex(glm::vec3 c) {
		coordinates = c;
	}
private:
	glm::vec3 coordinates;
};

class Mesh {
public:
	Mesh(Vertex* vertices, int numVertices);
	virtual ~Mesh();

	void draw(GLenum mode);

private:
	enum {POSITION_VB, NUM_BUFFERS};

	GLuint myVertexArrayObject;
	GLuint myVertexArrayBuffers[NUM_BUFFERS];
	unsigned int toDraw;
};
#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>

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
	Mesh(std::string path); //loading meshses from obj files
	Mesh(Vertex* vertices, int numVertices); //creating meshes manually
	virtual ~Mesh();

	void draw(GLenum mode);

private:
	enum {POSITION_VB, NUM_BUFFERS};

	GLuint myVertexArrayObject;
	GLuint myVertexArrayBuffers[NUM_BUFFERS];
	unsigned int toDraw;
};
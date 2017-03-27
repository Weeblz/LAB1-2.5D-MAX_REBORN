#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, int numVertices) {
	toDraw = numVertices;

	glGenVertexArrays(1, &myVertexArrayObject);
	glBindVertexArray(myVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, myVertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &myVertexArrayObject);
}

void Mesh::draw() {
	glBindVertexArray(myVertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, toDraw);

	glBindVertexArray(0);
}
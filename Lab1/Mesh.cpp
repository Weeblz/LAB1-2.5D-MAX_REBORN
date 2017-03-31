#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <tinyobjloader/tiny_obj_loader.h>
#include <iostream>
#include <vector>
#include "Mesh.h"

void LoadMesh(std::string path, std::vector<Vertex>& vertices) {
	//std::string inputfile = "res/ellipsoid.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				float vx = attrib.vertices[3 * idx.vertex_index + 0];
				float vy = attrib.vertices[3 * idx.vertex_index + 1];
				float vz = attrib.vertices[3 * idx.vertex_index + 2];
				vertices.push_back(Vertex({ vx, vy, vz }));
			}
			index_offset += fv;

			// per-face material
			//shapes[s].mesh.material_ids[f];
		}
	}
}

Mesh::Mesh(std::string path) {
	std::vector<Vertex> vertices;
	LoadMesh(path, vertices);

	Vertex* verts = vertices.data();
	int numVertices = vertices.size();

	this->Mesh::Mesh(verts, numVertices);
}

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

void Mesh::draw(GLenum mode) {
	glBindVertexArray(myVertexArrayObject);
	
	glDrawArrays(mode, 0, toDraw);

	glBindVertexArray(0);
}
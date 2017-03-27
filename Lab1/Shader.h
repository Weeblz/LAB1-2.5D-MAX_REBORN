#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"

class Shader {
public:
	Shader(const std::string& filename);
	virtual ~Shader();
	void bind();
	void update(const Transform& transform);
	
private:
	static const unsigned int NUM_SHADERS = 2;

	enum { TRANSFORM_U, NUM_UNIFORMS};

	GLuint myProgram;
	GLuint myShaders[NUM_SHADERS];
	GLuint myUniforms[NUM_UNIFORMS];
};
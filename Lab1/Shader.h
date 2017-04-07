#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader {
public:
	Shader(const std::string& filename);
	virtual ~Shader();
	void bind();
	void update(const Transform& transform, const Camera& cam, const glm::vec4 newColor, const int mode);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum { TRANSFORM_U, VIEW_PROJECTION_U, COLOR_U, PROJECTION_MODE_U, NUM_UNIFORMS};

	GLuint myProgram;
	GLuint myShaders[NUM_SHADERS];
	GLuint myUniforms[NUM_UNIFORMS];
};
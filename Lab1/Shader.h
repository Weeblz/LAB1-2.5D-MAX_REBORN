#pragma once
#include <string>
#include <GL\glew.h>

class Shader {
public:
	Shader(const std::string& filename);
	virtual ~Shader();
	void bind();
private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint myProgram;
	GLuint myShaders[NUM_SHADERS];
};
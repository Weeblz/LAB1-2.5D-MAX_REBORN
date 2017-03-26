#include "Shader.h"
#include <iostream>
#include <fstream>

static std::string loadShader(const std::string& filename) {
	std::fstream reading;
	reading.open(filename.c_str());

	std::string line, output;

	if (reading.is_open()) {
		while (reading.good()) {
			getline(reading, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Can't open the shader file.";
	}

	return output;
}

static void checkErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& Message) {
	GLint success;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << Message << ": " << error << "." << std::endl;
	}
}

static GLuint createShader(const std::string& text, GLenum type) {
	GLuint shader = glCreateShader(type);

	if (shader == 0) {
		std::cerr << "Shader creation failed." << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkErrors(shader, GL_COMPILE_STATUS, false, "Shader compilation failed.");

	return shader;
}

Shader::Shader(const std::string& filename) {
	myProgram = glCreateProgram();
	myShaders[0] = createShader(loadShader(filename + ".vs"), GL_VERTEX_SHADER);
	myShaders[1] = createShader(loadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(myProgram, myShaders[i]);
	}

	glBindAttribLocation(myProgram, 0, "position");

	glLinkProgram(myProgram);
	checkErrors(myProgram, GL_LINK_STATUS, true, "Program linking failed.");

	glValidateProgram(myProgram);
	checkErrors(myProgram, GL_VALIDATE_STATUS, true, "Program validating failed");
}

Shader::~Shader() {

}

void Shader::bind() {
	glUseProgram(myProgram);
}
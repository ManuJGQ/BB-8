#pragma once

#include <iostream>
#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <fstream>
#include <sstream>
#include "glm.hpp"

class PagShaderProgram
{
public:
	PagShaderProgram();
	~PagShaderProgram();
	
	GLuint createShaderProgram(const char *filename);
	bool use();

	bool setUniform(std::string name, GLfloat value);
	bool setUniform(std::string name, GLint value);
	bool setUniform(std::string name, glm::mat4 value);
	bool setUniform(std::string name, glm::vec3 value);

private:
	GLuint handler;
	bool linked;
	std::string logString;

	GLuint compileShader(const char *filename, GLenum shaderType);
	bool fileExists(const std::string & fileName);
};


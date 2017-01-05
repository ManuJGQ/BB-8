#pragma once

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

class PagMaterial{
	glm::vec3 Ka;
	glm::vec3 Kd;
public:
	PagMaterial();
	PagMaterial(glm::vec3 _Ka, glm::vec3 _Kd);
	PagMaterial(const PagMaterial &orig);
	glm::vec3 getKa() { return Ka; }
	glm::vec3 getKd() { return Kd; }
	~PagMaterial();
};


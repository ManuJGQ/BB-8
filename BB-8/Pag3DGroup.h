#pragma once

#include "Structs.h"
#include "Pag3DElement.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"
#include "PagRevolutionObject.h"

class Pag3DGroup : public Pag3DElement {
	Pag3DElement** elements;
	int numObjects;
	glm::mat4 ModelMatrix;
public:
	void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> shader, PagLight* light) override;
	void createObject() override;
	Pag3DGroup();
	Pag3DGroup(Structs::Fichero ficheros[], int _numObjects);
	Pag3DGroup(Pag3DGroup groups[], int _numObjects);
	Pag3DGroup(const Pag3DGroup &orig);
	void operator = (const Pag3DGroup &orig);

	void setModelMatrix(glm::mat4 _ModelMatrix, int element) {
			dynamic_cast<PagRevolutionObject*>(elements[numObjects - element])->setModelMatrix(_ModelMatrix);
	}

	~Pag3DGroup();
};


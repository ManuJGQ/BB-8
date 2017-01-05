#pragma once

#include "Pag3DElement.h"

class Pag3DObject : public Pag3DElement {
	glm::mat4 ModelMatrix;
public:
	void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> shader, PagLight* light) override = 0;
	void createObject() override = 0;
	Pag3DObject();
	~Pag3DObject();
};


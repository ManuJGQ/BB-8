#include "PagMaterial.h"

PagMaterial::PagMaterial() {
	Ka = glm::vec3(0.0, 0.0, 0.0);
	Kd = glm::vec3(0.0, 0.0, 0.0);
}

PagMaterial::PagMaterial(glm::vec3 _Ka, glm::vec3 _Kd) {
	Ka = _Ka;
	Kd = _Kd;
}

PagMaterial::PagMaterial(const PagMaterial & orig){
	Ka = orig.Ka;
	Kd = orig.Ka;
}

PagMaterial::~PagMaterial(){}

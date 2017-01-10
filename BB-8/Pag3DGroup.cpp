#include "Pag3DGroup.h"
#include "PagRevolutionObject.h"
#include "PagTable.h"

/**
* Funcion para pintar en modo solido todos los Pag3DElements que tenga
* el Group
*/
void Pag3DGroup::draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> shader, PagLight* light, int ns){
	for (int i = 0; i < numObjects; i++) {
		elements[i]->draw(ViewMatrix, ProjectionMatrix, renderer, shader, light, ns);
	}
}

/**
 * Constructor por defectos de Pag3DGroup
 */
Pag3DGroup::Pag3DGroup() : elements(nullptr), numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
}

/**
 * Constructor pasandole un conjunto de Ficheros txt
 */
Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numObjects) : numObjects(_numObjects + 1) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		if (i == 0)elements[i] = new PagTable();
		else elements[i] = new PagRevolutionObject(ficheros[i - 1]);
	}
}

/**
 *  Constructor pasandole un conjunto de objetos Pag3DGroup
 */
Pag3DGroup::Pag3DGroup(Pag3DGroup groups[], int _numObjects) : numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[_numObjects];
	for (int i = 0; i < _numObjects; i++) { elements[i] = new Pag3DGroup(groups[i]); }
}

/**
 * Constructor de copia de Pag3DGroup
 */
Pag3DGroup::Pag3DGroup(const Pag3DGroup& orig) : numObjects(orig.numObjects) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		PagRevolutionObject* object = dynamic_cast<PagRevolutionObject*>(orig.elements[i]);
		if (object != nullptr) {
			elements[i] = new PagRevolutionObject(*object);
		}
	}
}

/**
 * Operador igual de Pag3DGroup
 */
void Pag3DGroup::operator=(const Pag3DGroup& orig) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	numObjects = orig.numObjects;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		if(i == 0) {
			PagTable* object = dynamic_cast<PagTable*>(orig.elements[i]);
			if (object != nullptr) {
				elements[i] = new PagTable(*object);
			}
		}else {
			PagRevolutionObject* object = dynamic_cast<PagRevolutionObject*>(orig.elements[i]);
			if (object != nullptr) {
				elements[i] = new PagRevolutionObject(*object);
			}
		}
	}
}

/**
 * Funcion que crea los distintos Pag3DElements que tenga el Group
 */
void Pag3DGroup::createObject() {
	for (int i = 0; i < numObjects; i++) {
		elements[i]->createObject();
	}
}

/**
 * Destructor de Pag3DGroup
 */
Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numObjects; i++) {
		delete elements[i];
	}
	delete[] elements;
}

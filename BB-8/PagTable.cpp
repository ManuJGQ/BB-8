#include "PagTable.h"

PagTable::PagTable(){
	PuntosPerfil pointsTable[11] = {{ 0,0 },
									{ 30,0 },
									{ 60,0 },
									{ 90,0 },
									{ 120,0 },
									{ 150,1 },
									{ 120,1 },
									{ 90,1 },
									{ 60,1 },
									{ 30,1 },
									{ 0,1 }};
	table = PagRevolutionObject(11, 0, pointsTable, true, true, 100, "mesa", "Arena", "bump3", "Limpio");
}

void PagTable::createObject(){
	table.createObject();
}


void PagTable::draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> shader, PagLight* light, int ns){
	table.draw(ViewMatrix, ProjectionMatrix, renderer, shader, light, ns);
}

PagTable::PagTable(const PagTable & orig){
	*this = orig;
}

void PagTable::operator=(const PagTable & orig){
	table = orig.table;
}

PagTable::~PagTable(){}

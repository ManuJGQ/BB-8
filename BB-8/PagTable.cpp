#include "PagTable.h"

PagTable::PagTable(){
	PuntosPerfil pointsTable[11] = {{ 0,0 },
									{ 3,0 },
									{ 6,0 },
									{ 9,0 },
									{ 12,0 },
									{ 15,1 },
									{ 12,1 },
									{ 9,1 },
									{ 6,1 },
									{ 3,1 },
									{ 0,1 }};
	table = PagRevolutionObject(11, 0, pointsTable, true, true, 100, "mesa", "tronco");
}

void PagTable::createObject(){
	table.createObject();
}


void PagTable::draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer * renderer, PagLight* light){
	table.draw(ViewMatrix, ProjectionMatrix, renderer, light);
}

PagTable::PagTable(const PagTable & orig){
	*this = orig;
}

void PagTable::operator=(const PagTable & orig){
	table = orig.table;
}

PagTable::~PagTable(){}

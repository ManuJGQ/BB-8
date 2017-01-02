#pragma once

#include "glm.hpp"

#include "PagShaderProgram.h"

#include "PagSubdivisionProfile.h"
#include "Pag3DObject.h"

class PagRevolutionObject: public Pag3DObject{
	glm::mat4 ModelMatrix;

	//Flags para saber si tiene tapa
	bool flagBottomTape;
	bool flagTopTape;

	//Arrays que almacenan la geometria y Topologia
	Geometria *geometria;
	Geometria *geometriaBottomTape;
	Geometria *geometriaTopTape;
	CoordTexturas *coordtext;
	CoordTexturas *coordtextBottomTape;
	CoordTexturas *coordtextTopTape;
	int *indices;
	int *indicesBottomTape;
	int *indicesTopTape;

	int slices;
	int tamaGeometriaCoordText;
	int tamaIndices;

	//Arrays para los vbos y ibos
	PagVaoData *pointsColor;
	PagVaoData *pointsColorBottom;
	PagVaoData *pointsColorTop;
	GLuint *_indices;
	GLuint *_indicesTop;
	GLuint *_indicesBottom;;

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	GLuint vaoBottomTape;
	GLuint vboBottomTape;
	GLuint iboBottomTape;

	GLuint vaoTopTape;
	GLuint vboTopTape;
	GLuint iboTopTape;

	bool primitivasRellenadas;

	//String con el nombre de los txt
	std::string nombreAlumno;

	//Nombre de la textura que usara
	std::string nombreTextura;
public:
	PagSubdivisionProfile subdivisionProfiles;
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil *_perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape, int _slices, std::string _nombreAlumno, std::string _nombreTextura);
	PagRevolutionObject(Structs::Fichero _fichero);
	PagRevolutionObject(const PagRevolutionObject &orig);
	void operator = (const PagRevolutionObject &orig);
	void createObject() override;
	//void drawPointsCloud(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix) override;
	void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, PagLight* light) override;


	//Metodos Gets & Set

	Geometria& getGeometria() const { return *geometria; }
	Geometria& getGeometriaBottomTape() const { return *geometriaBottomTape; }
	Geometria& getGeometriaTopTape() const { return *geometriaTopTape; }

	CoordTexturas& getCoordText() const { return *coordtext; }
	CoordTexturas& getCoordTextBottomTape() const { return *coordtextBottomTape; }
	CoordTexturas& getCoordTextTopTape() const { return *coordtextTopTape; }

	int& getIndices() const { return *indices; }
	int& getIndicesBottomTape() const { return *indicesBottomTape; }
	int& getIndicesTopTape() const { return *indicesTopTape; }

	int getTamaGeometriaCoordText() const { return tamaGeometriaCoordText; }
	int getTamaIndices() const { return tamaIndices; }
	int getTamaIndicesTapes() const { return slices + 1; }

	bool getFlagBottomTape() const { return flagBottomTape; }
	bool getFlagTopTape() const { return flagTopTape; }

	std::string getNombreAlumno() const { return nombreAlumno; }

	void setModelMatrix(glm::mat4 _ModelMatrix) { ModelMatrix *= _ModelMatrix; }

	~PagRevolutionObject();
};


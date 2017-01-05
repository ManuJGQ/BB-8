#include "PagRevolutionObject.h"
#include "PagAssistantClass.h"

#include <math.h>
#include <string>

#include "PagRenderer.h"


#define PI 3.14159265358979323846

/**
 * Constructor por defecto de PagRevolutionObject
 */
PagRevolutionObject::PagRevolutionObject() : flagBottomTape(false), flagTopTape(false),
geometria(nullptr), geometriaBottomTape(nullptr), geometriaTopTape(nullptr), coordtext(nullptr),
coordtextBottomTape(nullptr), coordtextTopTape(nullptr), indices(nullptr), indicesBottomTape(nullptr),
indicesTopTape(nullptr), slices(0), tamaGeometriaCoordText(0), tamaIndices(0),
pointsColor(nullptr), pointsColorBottom(nullptr), pointsColorTop(nullptr), _indices(nullptr), _indicesTop(nullptr),
_indicesBottom(nullptr), primitivasRellenadas(false), material() {
};

/**
 * Constructor parametrizado de PagRevolutionObject
 */
PagRevolutionObject::PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil *_perfilOriginal,
	bool _flagBottomTape, bool _flagTopTape, int _slices, std::string _nombreAlumno, std::string _nombreTextura) : flagBottomTape(false), flagTopTape(false),
	geometria(nullptr), geometriaBottomTape(nullptr), geometriaTopTape(nullptr), coordtext(nullptr), coordtextBottomTape(nullptr),
	coordtextTopTape(nullptr), indices(nullptr), indicesBottomTape(nullptr), indicesTopTape(nullptr),
	tamaGeometriaCoordText(0), tamaIndices(0), pointsColor(nullptr), pointsColorBottom(nullptr), pointsColorTop(nullptr),
	_indices(nullptr), _indicesTop(nullptr), _indicesBottom(nullptr), primitivasRellenadas(false), nombreAlumno(_nombreAlumno), nombreTextura(_nombreTextura), material() {

	flagBottomTape = _flagBottomTape;
	flagTopTape = _flagTopTape;

	subdivisionProfiles = PagSubdivisionProfile(_numPuntosPerfilOriginal, _numDivisiones,
		_perfilOriginal);

	subdivisionProfiles.subdivisionPolilineas();

	slices = _slices;

	if (slices == 0) slices++;
	slices++;

}

/**
 * Constructor parametrizado de PagRevolutionObject, pasandole un Fichero txt
 */
PagRevolutionObject::PagRevolutionObject(Structs::Fichero _fichero) {
	PagAssistantClass f;
	*this = f.leerDatos(_fichero);
}

/**
* Constructor de copia de PagRevolutionObejct
*/
PagRevolutionObject::PagRevolutionObject(const PagRevolutionObject & orig) {
	*this = orig;
}

/**
* Operador igual de PagRevolutionObejct
*/
void PagRevolutionObject::operator=(const PagRevolutionObject & orig) {
	flagBottomTape = orig.flagBottomTape;
	flagTopTape = orig.flagTopTape;
	slices = orig.slices;
	tamaGeometriaCoordText = orig.tamaGeometriaCoordText;
	tamaIndices = orig.tamaIndices;
	subdivisionProfiles = orig.subdivisionProfiles;
	nombreAlumno = orig.nombreAlumno;
	nombreTextura = orig.nombreTextura;
	material = orig.material;

	if (orig.geometria != nullptr) {
		geometria = new Geometria[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			geometria[i].vertice = orig.geometria[i].vertice;
			geometria[i].normal = orig.geometria[i].normal;
			geometria[i].tangente = orig.geometria[i].tangente;
		}
	}
	else geometria = nullptr;

	if (orig.geometriaBottomTape != nullptr) {
		geometriaBottomTape = new Geometria[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			geometriaBottomTape[i].vertice = orig.geometriaBottomTape[i].vertice;
			geometriaBottomTape[i].normal = orig.geometriaBottomTape[i].normal;
			geometriaBottomTape[i].tangente = orig.geometriaBottomTape[i].tangente;
		}
	}
	else geometriaBottomTape = nullptr;

	if (orig.geometriaTopTape != nullptr) {
		geometriaTopTape = new Geometria[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			geometriaTopTape[i].vertice = orig.geometriaTopTape[i].vertice;
			geometriaTopTape[i].normal = orig.geometriaTopTape[i].normal;
			geometriaTopTape[i].tangente = orig.geometriaTopTape[i].tangente;
		}
	}
	else geometriaTopTape = nullptr;

	if (orig.coordtext != nullptr) {
		coordtext = new CoordTexturas[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			coordtext[i] = orig.coordtext[i];
		}
	}
	else coordtext = nullptr;

	if (orig.coordtextBottomTape != nullptr) {
		coordtextBottomTape = new CoordTexturas[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			coordtextBottomTape[i] = orig.coordtextBottomTape[i];
		}
	}
	else coordtextBottomTape = nullptr;

	if (orig.coordtextTopTape != nullptr) {
		coordtextTopTape = new CoordTexturas[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			coordtextTopTape[i] = orig.coordtextTopTape[i];
		}
	}
	else coordtextTopTape = nullptr;

	if (orig.indices != nullptr) {
		indices = new int[tamaIndices];
		for (int i = 0; i < tamaIndices; i++) {
			indices[i] = orig.indices[i];
		}
	}
	else indices = nullptr;

	if (orig.indicesBottomTape != nullptr) {
		indicesBottomTape = new int[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			indicesBottomTape[i] = orig.indicesBottomTape[i];
		}
	}
	else indicesBottomTape = nullptr;

	if (orig.indicesTopTape != nullptr) {
		indicesTopTape = new int[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			indicesTopTape[i] = orig.indicesTopTape[i];
		}
	}
	else indicesTopTape = nullptr;

	if (orig.pointsColor != nullptr) {
		pointsColor = new PagVaoData[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			pointsColor[i] = orig.pointsColor[i];
		}
	}
	else pointsColor = nullptr;

	if (orig.pointsColorBottom != nullptr) {
		pointsColorBottom = new PagVaoData[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			pointsColorBottom[i] = orig.pointsColorBottom[i];
		}
	}
	else pointsColorBottom = nullptr;

	if (orig.pointsColorTop != nullptr) {
		pointsColorTop = new PagVaoData[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			pointsColorTop[i] = orig.pointsColorTop[i];
		}
	}
	else pointsColorTop = nullptr;

	if (orig._indices != nullptr) {
		_indices = new GLuint[tamaIndices];
		for (int i = 0; i < tamaIndices; i++) {
			_indices[i] = orig._indices[i];
		}
	}
	else _indices = nullptr;

	if (orig._indicesBottom != nullptr) {
		_indicesBottom = new GLuint[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			_indicesBottom[i] = orig._indicesBottom[i];
		}
	}
	else _indicesBottom = nullptr;

	if (orig._indicesTop != nullptr) {
		_indicesTop = new GLuint[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			_indicesTop[i] = orig._indicesTop[i];
		}
	}
	else _indicesTop = nullptr;

}

/**
 * Funcion encargada de crear la Geometria y Topologia del PagRevolutionObject
 */
void PagRevolutionObject::createObject() {
	if (nombreAlumno == "mesa") material = PagMaterial(glm::vec3(0.55, 0.27, 0.07), glm::vec3(0.55, 0.27, 0.07));
	if (nombreAlumno == "b1") material = PagMaterial(glm::vec3(1.0, 0.55, 0.0), glm::vec3(1.0, 0.55, 0.0));
	if (nombreAlumno == "b2") material = PagMaterial(glm::vec3(0.36, 0.36, 0.36), glm::vec3(0.36, 0.36, 0.36));
	if (nombreAlumno == "b3") material = PagMaterial(glm::vec3(1.0, 0.55, 0.0), glm::vec3(1.0, 0.55, 0.0));
	if (nombreAlumno == "b4") material = PagMaterial(glm::vec3(1.0, 0.55, 0.0), glm::vec3(1.0, 0.55, 0.0));
	if (nombreAlumno == "b5") material = PagMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	if (nombreAlumno == "b6") material = PagMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	if (nombreAlumno == "b7") material = PagMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	if (nombreAlumno == "b8") material = PagMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));

	int numPuntosPerfil = subdivisionProfiles.getNumPuntosPerfil();

	int numTapas = 0;
	int cambioIndice = 0;
	int cambioIndiceTop = 0;
	if (flagBottomTape) {
		numTapas++;
		cambioIndice++;
		geometriaBottomTape = new Geometria[slices + 1];
		coordtextBottomTape = new CoordTexturas[slices + 1];
		indicesBottomTape = new int[slices + 1];
		pointsColorBottom = new PagVaoData[slices + 1];
		_indicesBottom = new GLuint[slices + 1];
	}
	if (flagTopTape) {
		numTapas++;
		cambioIndiceTop++;
		geometriaTopTape = new Geometria[slices + 1];
		coordtextTopTape = new CoordTexturas[slices + 1];
		indicesTopTape = new int[slices + 1];
		pointsColorTop = new PagVaoData[slices + 1];
		_indicesTop = new GLuint[slices + 1];
	}

	tamaGeometriaCoordText = (numPuntosPerfil - numTapas) * slices;
	tamaIndices = (((numPuntosPerfil - (numTapas)) * 2) + 1) * slices;
	geometria = new Geometria[tamaGeometriaCoordText];
	coordtext = new CoordTexturas[tamaGeometriaCoordText];
	pointsColor = new PagVaoData[tamaGeometriaCoordText];
	indices = new int[tamaIndices];
	_indices = new GLuint[tamaIndices];

	PuntosPerfil *perfil = &subdivisionProfiles.getPerfil();

	double angleRadIncrement = (2 * PI) / (slices - 1);

	// VERTICES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometriaBottomTape[slices].vertice = vert;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometriaTopTape[slices].vertice = vert;
		}
		else {
			for (int i = 0; i < slices; i++) {
				PuntosVertices vert;
				if (i == slices - 1) {
					vert = geometria[(j - cambioIndice) * slices].vertice;
				}
				else {
					double x = perfil[j].x * cos(angleRadIncrement * i);
					double z = perfil[j].x * -sin(angleRadIncrement * i);

					vert.x = x;
					vert.y = perfil[j].y;
					vert.z = z;
				}

				geometria[(j - cambioIndice) * slices + i].vertice = vert;
				if (j == 1 && flagBottomTape) geometriaBottomTape[i].vertice = vert;
				if (j == numPuntosPerfil - 2 && flagTopTape) geometriaTopTape[i].vertice = vert;
			}
		}

	}


	// NORMALES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = -1;
			normal.z = 0;

			geometriaBottomTape[slices].normal = normal;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = 1;
			normal.z = 0;

			geometriaTopTape[slices].normal = normal;
		}
		else {
			PuntosVertices p1;
			PuntosVertices p2;

			if (j == 0) p1 = { 0,0,0 };
			else if (j == 1 && flagBottomTape) p1 = geometriaBottomTape[slices].vertice;
			else p1 = geometria[(j - cambioIndice - 1) * slices].vertice;

			PuntosVertices pi = geometria[(j - cambioIndice) * slices].vertice;

			if (j == numPuntosPerfil - 1)  p2 = { 0,0,0 };
			else if (j == numPuntosPerfil - 2 && flagTopTape) p2 = geometriaTopTape[slices].vertice;
			else p2 = geometria[(j - cambioIndice + 1) * slices].vertice;

			PuntosVertices v1;
			v1.x = pi.x - p1.x;
			v1.y = pi.y - p1.y;
			v1.z = pi.z - p1.z;

			double modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
			v1.x = v1.x / modV1;
			v1.y = v1.y / modV1;
			v1.z = v1.z / modV1;

			double xTemp = v1.x;
			v1.x = v1.y;
			v1.y = xTemp * -1;

			PuntosVertices vi;
			vi.x = p2.x - pi.x;
			vi.y = p2.y - pi.y;
			vi.z = p2.z - pi.z;

			double modVi = sqrt((vi.x * vi.x) + (vi.y * vi.y) + (vi.z * vi.z));
			vi.x = vi.x / modVi;
			vi.y = vi.y / modVi;
			vi.z = vi.z / modVi;

			xTemp = vi.x;
			vi.x = vi.y;
			vi.y = xTemp * -1;

			if (j == 0) v1 = vi;
			if (j == numPuntosPerfil - 1) vi = v1;

			NormalesTangentes normal;

			normal.x = (v1.x + vi.x) / 2;
			normal.y = (v1.y + vi.y) / 2;
			normal.z = (v1.z + vi.z) / 2;

			for (int i = 0; i < slices; i++) {
				NormalesTangentes normal2;
				normal2.x = normal.x * cos(angleRadIncrement * i);
				normal2.z = normal.x * -sin(angleRadIncrement * i);
				normal2.y = normal.y;
				geometria[(j - cambioIndice) * slices + i].normal = normal2;
				if (j == numPuntosPerfil - 2 && flagTopTape) {
					geometriaTopTape[i].normal = normal2;
				}
				if (j == 1 && flagBottomTape) {
					geometriaBottomTape[i].normal = normal2;
				}
			}

		}

	}

	// TANGENTES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometriaBottomTape[slices].tangente = tangente;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometriaTopTape[slices].tangente = tangente;
		}
		else {
			for (int i = 0; i < slices; i++) {
				NormalesTangentes tangente;

				tangente.x = -1 * sin(angleRadIncrement * i);
				tangente.y = 0;
				tangente.z = -1 * cos(angleRadIncrement * i);

				geometria[(j - cambioIndice) * slices + i].tangente = tangente;
				if (j == 1 && flagBottomTape) geometriaBottomTape[i].tangente = tangente;
				if (j == numPuntosPerfil - 2 && flagTopTape) geometriaTopTape[i].tangente = tangente;
			}
		}
	}

	// COORDENADAS TEXTURAS

	if (flagBottomTape || flagTopTape) {
		for (int i = 0; i < slices; i++) {
			double s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
			double t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
			if (flagBottomTape) {
				coordtextBottomTape[i].s = s;
				coordtextBottomTape[i].t = t;
			}
			if (flagTopTape) {
				coordtextTopTape[i].s = s;
				coordtextTopTape[i].t = t;
			}
		}
		if (flagBottomTape) {
			coordtextBottomTape[slices].s = 0.5;
			coordtextBottomTape[slices].t = 0.5;
		}
		if (flagTopTape) {
			coordtextTopTape[slices].s = 0.5;
			coordtextTopTape[slices].t = 0.5;
		}
	}

	double *modulo = new double[numPuntosPerfil - numTapas];

	for (int j = 0; j < slices; j++) {
		double s = j * double(float(1) / float(slices - 1));

		double sumatorio = 0;

		modulo[0] = sumatorio;

		for (int i = 1; i < numPuntosPerfil - numTapas; i++) {

			PuntosVertices p1 = geometria[i * slices + j].vertice;
			PuntosVertices p2 = geometria[(i - 1) * slices + j].vertice;

			PuntosVertices v1;
			v1.x = p1.x - p2.x;
			v1.y = p1.y - p2.y;
			v1.z = p1.z - p2.z;

			double modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

			sumatorio += modV1;

			modulo[i] = sumatorio;
		}

		for (int i = cambioIndice; i < numPuntosPerfil - cambioIndiceTop; i++) {

			double t = (modulo[i - cambioIndice]) / (sumatorio);

			coordtext[(i - cambioIndice) * slices + j].s = s;
			coordtext[(i - cambioIndice) * slices + j].t = t;
		}
	}

	delete[] modulo;

	// INDICES

	if (flagBottomTape) {
		for (int i = 0; i < slices; i++) {
			indicesBottomTape[i + 1] = slices - 1 - i;
		}
		indicesBottomTape[0] = slices;
	}
	if (flagTopTape) {
		for (int i = 0; i < slices; i++) {
			indicesTopTape[i] = i;
		}
		indicesTopTape[slices] = slices;
	}
	int k = 0;
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < numPuntosPerfil - numTapas; j++) {
			indices[k] = i + (j * slices);
			indices[k + 1] = ((i + 1) % slices) + (j * slices);
			k += 2;
		}
		indices[k] = 0xFFFF;
		k++;
	}
	//std::cout << slices << std::endl;

	PagAssistantClass f;
	f.devolverDatos(*this);

	//Arrays para los vbos y ibos
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		pointsColor[i] = { glm::vec3((GLfloat)geometria[i].vertice.x, (GLfloat)geometria[i].vertice.y, (GLfloat)geometria[i].vertice.z),
			glm::vec3(0.85, 0.65, 0.12),
			glm::vec3((GLfloat)geometria[i].normal.x, (GLfloat)geometria[i].normal.y, (GLfloat)geometria[i].normal.z),
			glm::vec2((GLfloat)coordtext[i].s, (GLfloat)coordtext[i].t),
			glm::vec3((GLfloat)geometria[i].tangente.x, (GLfloat)geometria[i].tangente.y, (GLfloat)geometria[i].tangente.z) };
	}

	for (int i = 0; i < tamaIndices; i++) {
		_indices[i] = (GLuint)indices[i];
	}

	if (flagBottomTape) {
		for (int i = 0; i < slices + 1; i++) {
			pointsColorBottom[i] = { glm::vec3((GLfloat)geometriaBottomTape[i].vertice.x, (GLfloat)geometriaBottomTape[i].vertice.y, (GLfloat)geometriaBottomTape[i].vertice.z),
				glm::vec3(0.85, 0.65, 0.12),
				glm::vec3((GLfloat)geometriaBottomTape[i].normal.x, (GLfloat)geometriaBottomTape[i].normal.y, (GLfloat)geometriaBottomTape[i].normal.z),
				glm::vec2((GLfloat)coordtextBottomTape[i].s, (GLfloat)coordtextBottomTape[i].t),
				glm::vec3((GLfloat)geometriaBottomTape[i].tangente.x, (GLfloat)geometriaBottomTape[i].tangente.y, (GLfloat)geometriaBottomTape[i].tangente.z)
			};
		}

		for (int i = 0; i < slices + 1; i++) {
			_indicesBottom[i] = (GLuint)indicesBottomTape[i];
		}
	}

	if (flagTopTape) {
		for (int i = 0; i < slices + 1; i++) {
			pointsColorTop[i] = { glm::vec3((GLfloat)geometriaTopTape[i].vertice.x, (GLfloat)geometriaTopTape[i].vertice.y, (GLfloat)geometriaTopTape[i].vertice.z),
				glm::vec3(0.85, 0.65, 0.12),
				glm::vec3((GLfloat)geometriaTopTape[i].normal.x, (GLfloat)geometriaTopTape[i].normal.y, (GLfloat)geometriaTopTape[i].normal.z),
				glm::vec2((GLfloat)coordtextTopTape[i].s, (GLfloat)coordtextTopTape[i].t),
				glm::vec3((GLfloat)geometriaTopTape[i].tangente.x, (GLfloat)geometriaTopTape[i].tangente.y, (GLfloat)geometriaTopTape[i].tangente.z)
			};
		}

		for (int i = 0; i < slices + 1; i++) {
			_indicesTop[i] = (GLuint)indicesTopTape[i];
		}
	}
}

/**
 * Funcion encargada de pintar el PagRevolutionObject en todos los modos posibles
 */
void PagRevolutionObject::draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> _shader, PagLight* light) {
	std::string nShader = _shader.first;

	if (nShader == "points" || nShader == "pointsMultiColor") {
		if (nShader == "points") {
			PagShaderProgram* shader = _shader.second;

			shader->use();

			if(!shader->getUniformsRealizados()) {
				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("vColor", glm::vec3(0.85, 0.65, 0.12));
				shader->setUniform("pointSize", 4.0f);

				shader->setUniformsRealizados(true);
			}
			

			if(!primitivasRellenadas) {
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);

				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices), _indices, GL_STATIC_DRAW);
			}

			glBindVertexArray(vao);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glDrawElements(GL_POINTS, (sizeof(GLuint) * (tamaIndices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

			if (flagBottomTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoBottomTape);
					glBindVertexArray(vaoBottomTape);
					glGenBuffers(1, &vboBottomTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboBottomTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorBottom, GL_STATIC_DRAW);

					glGenBuffers(1, &iboBottomTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);
				}
				
				glBindVertexArray(vaoBottomTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}

			if (flagTopTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoTopTape);
					glBindVertexArray(vaoTopTape);
					glGenBuffers(1, &vboTopTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboTopTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorTop, GL_STATIC_DRAW);

					glGenBuffers(1, &iboTopTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);
				}

				glBindVertexArray(vaoTopTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}
		}
		if (nShader == "pointsMultiColor") {
			PagShaderProgram* shader = _shader.second;

			shader->use();

			if(!shader->getUniformsRealizados()) {
				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("pointSize", 4.0f);
				
				shader->setUniformsRealizados(true);
			}

			if(!primitivasRellenadas) {
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COLORS
					((GLubyte *)nullptr + (sizeof(glm::vec3))));

				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);

				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices), _indices, GL_STATIC_DRAW);
			}

			glBindVertexArray(vao);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glDrawElements(GL_POINTS, (sizeof(GLuint) * (tamaIndices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

			if (flagBottomTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoBottomTape);
					glBindVertexArray(vaoBottomTape);
					glGenBuffers(1, &vboBottomTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboBottomTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COLORS
						((GLubyte *)nullptr + (sizeof(glm::vec3))));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorBottom, GL_STATIC_DRAW);

					glGenBuffers(1, &iboBottomTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);
				}

				glBindVertexArray(vaoBottomTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}

			if (flagTopTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoTopTape);
					glBindVertexArray(vaoTopTape);
					glGenBuffers(1, &vboTopTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboTopTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COLORS
						((GLubyte *)nullptr + (sizeof(glm::vec3))));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorTop, GL_STATIC_DRAW);

					glGenBuffers(1, &iboTopTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);
				}	

				glBindVertexArray(vaoTopTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}
		}
	}
	else {
		if (nShader == "ADS-P" || nShader == "ADS-D" || nShader == "ADS-S") {
			char l = light->light;
			PagShaderProgram* shader = _shader.second;

			shader->use();

			if (l == 'P' && !shader->getUniformsRealizados()) {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightPosition", glm::vec3(ViewMatrix * glm::vec4(light->position, 1.0)));
				shader->setUniform("Ka", material.getKa());
				shader->setUniform("Kd", material.getKd());
				shader->setUniform("Ks", light->Ks);
				shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Shininess", light->shininess);

				shader->setUniformsRealizados(true);
			}
			else if (l == 'D' && !shader->getUniformsRealizados()) {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightDirection", glm::vec3(ViewMatrix * glm::vec4(light->direction, 0.0)));
				shader->setUniform("Ka", material.getKa());
				shader->setUniform("Kd", material.getKd());
				shader->setUniform("Ks", light->Ks);
				shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Shininess", light->shininess);

				shader->setUniformsRealizados(true);
			}
			else if (l == 'S' && !shader->getUniformsRealizados()) {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightPosition", glm::vec3(ViewMatrix * glm::vec4(light->position, 1.0)));
				shader->setUniform("lightDirection", glm::vec3(ViewMatrix * glm::vec4(light->direction, 0.0)));
				shader->setUniform("Ka", material.getKa());
				shader->setUniform("Kd", material.getKd());
				shader->setUniform("Ks", light->Ks);
				shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
				shader->setUniform("Shininess", light->shininess);
				shader->setUniform("y", light->y);
				shader->setUniform("s", light->s);

				shader->setUniformsRealizados(true);
			}

			if(!primitivasRellenadas) {
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
					((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);

				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices), _indices, GL_STATIC_DRAW);
			}
			
			glBindVertexArray(vao);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glEnable(GL_PRIMITIVE_RESTART);
			glPrimitiveRestartIndex(0xFFFF);
			glDrawElements(GL_TRIANGLE_STRIP, (sizeof(GLuint) * (tamaIndices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

			if (flagBottomTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoBottomTape);
					glBindVertexArray(vaoBottomTape);
					glGenBuffers(1, &vboBottomTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboBottomTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
						((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorBottom, GL_STATIC_DRAW);

					glGenBuffers(1, &iboBottomTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);
				}

				glBindVertexArray(vaoBottomTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}

			if (flagTopTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoTopTape);
					glBindVertexArray(vaoTopTape);
					glGenBuffers(1, &vboTopTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboTopTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
						((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorTop, GL_STATIC_DRAW);

					glGenBuffers(1, &iboTopTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);
				}				

				glBindVertexArray(vaoTopTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}
		}
		if (nShader == "Test") {
			PagShaderProgram* shader = _shader.second;

			shader->use();

			if(!shader->getUniformsRealizados()) {
				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("pointSize", 4.0f);

				shader->setUniformsRealizados(true);
			}

			if(!primitivasRellenadas) {
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);

				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices), _indices, GL_STATIC_DRAW);
			}

			glBindVertexArray(vao);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glEnable(GL_PRIMITIVE_RESTART);
			glPrimitiveRestartIndex(0xFFFF);
			glDrawElements(GL_TRIANGLE_STRIP, (sizeof(GLuint) * (tamaIndices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

			if (flagBottomTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoBottomTape);
					glBindVertexArray(vaoBottomTape);
					glGenBuffers(1, &vboBottomTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboBottomTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorBottom, GL_STATIC_DRAW);

					glGenBuffers(1, &iboBottomTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);
				}

				glBindVertexArray(vaoBottomTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}

			if (flagTopTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoTopTape);
					glBindVertexArray(vaoTopTape);
					glGenBuffers(1, &vboTopTape);
					glBindBuffer(GL_ARRAY_BUFFER, vboTopTape);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
						GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
						((GLubyte *)nullptr + (0)));

					glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorTop, GL_STATIC_DRAW);

					glGenBuffers(1, &iboTopTape);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);
				}

				glBindVertexArray(vaoTopTape);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}
		}
		if (nShader == "Texture-P" || nShader == "Texture-D" || nShader == "Texture-S") {
			char l = light->light;
			PagShaderProgram* shader = _shader.second;

			shader->use();

			if (l == 'P') {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightPosition", glm::vec3(ViewMatrix * glm::vec4(light->position, 1.0)));
				if (!shader->getUniformsRealizados()) {
					shader->setUniform("Ks", light->Ks);
					shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Shininess", light->shininess);
					shader->setUniform("TexSamplerColor", 0);

					shader->setUniformsRealizados(true);
				}
			}
			else if (l == 'D') {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightDirection", glm::vec3(ViewMatrix * glm::vec4(light->direction, 0.0)));
				if(!shader->getUniformsRealizados()) {
					shader->setUniform("Ks", light->Ks);
					shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Shininess", light->shininess);
					shader->setUniform("TexSamplerColor", 0);

					shader->setUniformsRealizados(true);
				}
			}
			else if (l == 'S') {

				shader->setUniform("mvpMatrix", ProjectionMatrix * ViewMatrix * ModelMatrix);
				shader->setUniform("mModelView", ViewMatrix * ModelMatrix);
				shader->setUniform("lightPosition", glm::vec3(ViewMatrix * glm::vec4(light->position, 1.0)));
				shader->setUniform("lightDirection", glm::vec3(ViewMatrix * glm::vec4(light->direction, 0.0)));
				if(!shader->getUniformsRealizados()) {

					shader->setUniform("Ks", light->Ks);
					shader->setUniform("Ia", light->Ia * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Id", light->Id * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Is", light->Is * glm::vec3(1.0, 1.0, 1.0));
					shader->setUniform("Shininess", light->shininess);
					shader->setUniform("y", light->y);
					shader->setUniform("s", light->s);
					shader->setUniform("TexSamplerColor", 0);

					shader->setUniformsRealizados(true);
				}
			}

			if(!primitivasRellenadas) {
				glGenVertexArrays(1, &vao);
				glGenBuffers(1, &vbo);
				glGenBuffers(1, &ibo);
			}

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
				((GLubyte *)nullptr + (0)));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
				((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COORDTEXTS
				((GLubyte *)nullptr + 3 * (sizeof(glm::vec3))));

			glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices), _indices, GL_STATIC_DRAW);

			glBindVertexArray(vao);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, renderer->getTexture(nombreTextura));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glEnable(GL_PRIMITIVE_RESTART);
			glPrimitiveRestartIndex(0xFFFF);
			glDrawElements(GL_TRIANGLE_STRIP, (sizeof(GLuint) * (tamaIndices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

			if (flagBottomTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoBottomTape);
					glGenBuffers(1, &vboBottomTape);
					glGenBuffers(1, &iboBottomTape);
				}
				
				glBindVertexArray(vaoBottomTape);
				glBindBuffer(GL_ARRAY_BUFFER, vboBottomTape);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
					((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COORDTEXTS
					((GLubyte *)nullptr + 3 * (sizeof(glm::vec3))));

				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorBottom, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);

				glBindVertexArray(vaoBottomTape);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, renderer->getTexture(nombreTextura));

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}

			if (flagTopTape) {
				if(!primitivasRellenadas) {
					glGenVertexArrays(1, &vaoTopTape);
					glGenBuffers(1, &vboTopTape);
					glGenBuffers(1, &iboTopTape);
				}
				
				glBindVertexArray(vaoTopTape);
				glBindBuffer(GL_ARRAY_BUFFER, vboTopTape);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//POSITIONS
					((GLubyte *)nullptr + (0)));

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//NORMALS
					((GLubyte *)nullptr + 2 * (sizeof(glm::vec3))));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
					GL_FLOAT, GL_FALSE, sizeof(PagVaoData),						//COORDTEXTS
					((GLubyte *)nullptr + 3 * (sizeof(glm::vec3))));


				glBufferData(GL_ARRAY_BUFFER, sizeof(PagVaoData) * (slices + 1), pointsColorTop, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);

				glBindVertexArray(vaoTopTape);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, renderer->getTexture(nombreTextura));

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
				glDrawElements(GL_TRIANGLE_FAN, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
			}
		}
	}
	if (!primitivasRellenadas)primitivasRellenadas = true;
}

/**
 * Destructor de PagRevolutionObject
 */
PagRevolutionObject::~PagRevolutionObject() {
	if (geometria != nullptr) delete[] geometria;
	if (geometriaBottomTape != nullptr) delete[] geometriaBottomTape;
	if (geometriaTopTape != nullptr) delete[] geometriaTopTape;
	if (coordtext != nullptr) delete[] coordtext;
	if (coordtextBottomTape != nullptr) delete[] coordtextBottomTape;
	if (coordtextTopTape != nullptr) delete[] coordtextTopTape;
	if (indices != nullptr) delete[] indices;
	if (indicesBottomTape != nullptr) delete[] indicesBottomTape;
	if (indicesTopTape != nullptr) delete[] indicesTopTape;
	if (pointsColor != nullptr) delete[] pointsColor;
	if (pointsColorTop != nullptr) delete[] pointsColorTop;
	if (pointsColorBottom != nullptr) delete[] pointsColorBottom;
	if (_indices != nullptr) delete[] _indices;
	if (_indicesBottom != nullptr) delete[] _indicesTop;
	if (_indicesTop != nullptr) delete[] _indicesBottom;
}

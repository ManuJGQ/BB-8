#pragma once

#include <iostream>
#include "glm.hpp"

namespace Structs {
	struct PuntosPerfil {
		double x;
		double y;
	};

	struct PuntosVertices {
		double x;
		double y;
		double z;
	};

	struct NormalesTangentes {
		double x;
		double y;
		double z;
	};

	struct CoordTexturas {
		double s;
		double t;
	};

	struct Geometria {
		PuntosVertices vertice;
		NormalesTangentes normal;
		NormalesTangentes tangente;
	};

	struct Fichero {
		std::string archivoIN;
		int numSlices;
		std::string nombreAlumno;
		std::string nTextura;
		std::string nSemiTrasnparente;
		std::string nBump;
	};

	struct PagVaoData {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
		glm::vec2 coordtext;
		glm::vec3 tangent;
	};

}

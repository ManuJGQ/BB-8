#include "PagAssistantClass.h"

#include <fstream>
#include <string>

#define Epsilon 0.000001

/**
 * Constructor por defectos de PagAssistantClass
 */
PagAssistantClass::PagAssistantClass() {}

/**
 * Funcion encargada de leer ficheros txt del disco
 */
PagRevolutionObject PagAssistantClass::leerDatos(Structs::Fichero _fichero) const {
	int slices = _fichero.numSlices;
	std::string nombreAlumno = _fichero.nombreAlumno;
	std::string archivo = _fichero.archivoIN;
	std::string nombreTextura = _fichero.nTextura;
	bool flagBottomTape = false;
	bool flagTopTape = false;

	int linea;
	linea = nombreAlumno.find('-');
	nombreAlumno = nombreAlumno.substr(0, linea);

	std::string linea_actual;
	int numPuntosPerfilOriginal;
	int numDivisiones;
	int coma;
	try {
		// Leemos la primera linea del archivo
		std::ifstream archivoPuntosPerfil;
		archivoPuntosPerfil.open(archivo);

		if (!archivoPuntosPerfil.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntosPerfilOriginal = stoi(linea_actual.substr(0, coma));
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntosPerfilOriginal < 2) throw std::string("Se necesitan 2 o mas puntos");
		if (numDivisiones < 0) throw std::string("No se permite un numero negativo de divisiones");

		PuntosPerfil *perfil = new PuntosPerfil[numPuntosPerfilOriginal];
		PuntosPerfil puntos;

		int alturaMasBaja = 0;

		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if ((puntos.x < 0) ||
				(puntos.x == 0 && (i > 0 && i < numPuntosPerfilOriginal - 1))) {
				numPuntosPerfilOriginal--;
				i--;
			}
			else {
				if (puntos.x == 0) {
					if (i == 0) flagBottomTape = true;
					if (i == numPuntosPerfilOriginal - 1) flagTopTape = true;
				}

				puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

				if (puntos.y < alturaMasBaja) {
					alturaMasBaja = puntos.y;
				}

				perfil[i] = puntos;

			}

		}

		archivoPuntosPerfil.close();

		if (alturaMasBaja < 1) {
			alturaMasBaja *= -1;

			for (int i = 0; i < numPuntosPerfilOriginal; i++) {
				perfil[i].y += (alturaMasBaja + 1);
			}
		}

		PuntosPerfil *perfilTemp = new PuntosPerfil[numPuntosPerfilOriginal];
		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			perfilTemp[i] = perfil[i];
		}

		delete[] perfil;

		perfil = perfilTemp;

		return PagRevolutionObject(numPuntosPerfilOriginal, numDivisiones, perfil,
			flagBottomTape, flagTopTape, slices, nombreAlumno, nombreTextura);

	}
	catch (std::string &e) {
		std::cout << "ERROR: " << e << std::endl;
	}
}

/**
* Funcion encargada de escribir los ficheros txt en disco
*/
void PagAssistantClass::devolverDatos(const PagRevolutionObject &orig) {
	std::string nombreAlumno = orig.getNombreAlumno();
	Geometria *geometria = &orig.getGeometria();
	CoordTexturas *coordtext = &orig.getCoordText();
	int *indices = &orig.getIndices();
	int tamaGeometriaCoordText = orig.getTamaGeometriaCoordText();
	int tamaIndices = orig.getTamaIndices();
	int tamaIndicesTapes = 0;
	if (orig.getFlagBottomTape() || orig.getFlagTopTape())tamaIndicesTapes = orig.getTamaIndicesTapes();

	char* docdir = getenv("userprofile");
	std::string path = docdir;
	path += "/Desktop/Geometry/";
	path += nombreAlumno;
	std::string nombreFichero;

	//ARCHIVO GEOMETRIA

	nombreFichero = path;
	nombreFichero += "-out-geom.txt";
	std::ofstream ficheroGeom;
	ficheroGeom.open(nombreFichero);
	ficheroGeom << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroGeom << geometria[i].vertice.x << ","
			<< geometria[i].vertice.y << ","
			<< geometria[i].vertice.z << ","
			<< geometria[i].normal.x << ","
			<< geometria[i].normal.y << ","
			<< geometria[i].normal.z << ","
			<< geometria[i].tangente.x << ","
			<< geometria[i].tangente.y << ","
			<< geometria[i].tangente.z << std::endl;
	}
	ficheroGeom.close();

	//ARCHIVO COORDTEXT

	nombreFichero = path;
	nombreFichero += "-out-text.txt";
	std::ofstream ficheroText;
	ficheroText.open(nombreFichero);
	ficheroText << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroText << coordtext[i].s << ","
			<< coordtext[i].t << std::endl;
	}
	ficheroText.close();

	//ARCHIVOS INDICES

	nombreFichero = path;
	nombreFichero += "-out-ind.txt";
	std::ofstream ficheroInd;
	ficheroInd.open(nombreFichero);
	ficheroInd << tamaIndices << std::endl;
	for (int i = 0; i < tamaIndices; i++) {
		ficheroInd << indices[i] << std::endl;
	}
	ficheroInd.close();

	//ARCHIVOS TAPAS

	if (orig.getFlagBottomTape()) {
		Geometria *geometriaBottom = &orig.getGeometriaBottomTape();
		CoordTexturas *coordtextBottom = &orig.getCoordTextBottomTape();
		int *indicesBottom = &orig.getIndicesBottomTape();

		//ARCHIVO GEOMETRIA TAPA ABAJO

		nombreFichero = path;
		nombreFichero += "-out-geom_BottomTape.txt";
		std::ofstream ficheroGeomBottom;
		ficheroGeomBottom.open(nombreFichero);
		ficheroGeomBottom << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroGeomBottom << geometriaBottom[i].vertice.x << ","
				<< geometriaBottom[i].vertice.y << ","
				<< geometriaBottom[i].vertice.z << ","
				<< geometriaBottom[i].normal.x << ","
				<< geometriaBottom[i].normal.y << ","
				<< geometriaBottom[i].normal.z << ","
				<< geometriaBottom[i].tangente.x << ","
				<< geometriaBottom[i].tangente.y << ","
				<< geometriaBottom[i].tangente.z << std::endl;
		}
		ficheroGeomBottom.close();

		//ARCHIVO COORDTEXT TAPA ABAJO

		nombreFichero = path;
		nombreFichero += "-out-text_BottomTape.txt";
		std::ofstream ficheroTextBottom;
		ficheroTextBottom.open(nombreFichero);
		ficheroTextBottom << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroTextBottom << coordtextBottom[i].s << ","
				<< coordtextBottom[i].t << std::endl;
		}
		ficheroTextBottom.close();

		//ARCHIVO INDICES TAPA ABAJO

		nombreFichero = path;
		nombreFichero += "-out-ind_BottomTape.txt";
		std::ofstream ficheroIndBottom;
		ficheroIndBottom.open(nombreFichero);
		ficheroIndBottom << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroIndBottom << indicesBottom[i] << std::endl;
		}
		ficheroIndBottom.close();
	}

	if (orig.getFlagTopTape()) {
		Geometria *geometriaTop = &orig.getGeometriaTopTape();
		CoordTexturas *coordtextTop = &orig.getCoordTextTopTape();
		int *indicesTop = &orig.getIndicesTopTape();

		//ARCHIVO GEOMETRIA TAPA ARRIBA

		nombreFichero = path;
		nombreFichero += "-out-geom_TopTape.txt";
		std::ofstream ficheroGeomTop;
		ficheroGeomTop.open(nombreFichero);
		ficheroGeomTop << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroGeomTop << geometriaTop[i].vertice.x << ","
				<< geometriaTop[i].vertice.y << ","
				<< geometriaTop[i].vertice.z << ","
				<< geometriaTop[i].normal.x << ","
				<< geometriaTop[i].normal.y << ","
				<< geometriaTop[i].normal.z << ","
				<< geometriaTop[i].tangente.x << ","
				<< geometriaTop[i].tangente.y << ","
				<< geometriaTop[i].tangente.z << std::endl;
		}
		ficheroGeomTop.close();

		//ARCHIVO COORDTEXT TAPA ARRIBA

		nombreFichero = path;
		nombreFichero += "-out-text_TopTape.txt";
		std::ofstream ficheroTextTop;
		ficheroTextTop.open(nombreFichero);
		ficheroTextTop << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroTextTop << coordtextTop[i].s << ","
				<< coordtextTop[i].t << std::endl;
		}
		ficheroTextTop.close();

		//ARCHIVO INDICES TAPA ARRIBA

		nombreFichero = path;
		nombreFichero += "-out-ind_TopTape.txt";
		std::ofstream ficheroIndTop;
		ficheroIndTop.open(nombreFichero);
		ficheroIndTop << tamaIndicesTapes << std::endl;
		for (int i = 0; i < tamaIndicesTapes; i++) {
			ficheroIndTop << indicesTop[i] << std::endl;
		}
		ficheroIndTop.close();
	}
}

 /**
 * Destructor de Pag3AssistantClass
 */
PagAssistantClass::~PagAssistantClass() {}

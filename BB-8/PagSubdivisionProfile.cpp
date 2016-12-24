#include "PagSubdivisionProfile.h"

/**
 * Constructor por defecto de PagSubdivisionProfile
 */
PagSubdivisionProfile::PagSubdivisionProfile() : perfilOriginal(nullptr),
perfilSubdividido(nullptr), numDivisiones(0), numPuntosPerfilOriginal(0), numPuntosPerfilSubdividido(0) {};

/**
 * Constructor parametrizado de PagSubdivisionProfile
 */
PagSubdivisionProfile::PagSubdivisionProfile(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil *_perfilOriginal) : numDivisiones(_numDivisiones),
	numPuntosPerfilOriginal(_numPuntosPerfilOriginal) {

	perfilOriginal = new PuntosPerfil[numPuntosPerfilOriginal];
	for (int i = 0; i < numPuntosPerfilOriginal; i++) {
		perfilOriginal[i] = _perfilOriginal[i];
	}

	numPuntosPerfilSubdividido = numPuntosPerfilOriginal;
	perfilSubdividido = new PuntosPerfil[numPuntosPerfilSubdividido];
	for (int i = 0; i < numPuntosPerfilSubdividido; i++) {
		perfilSubdividido[i] = perfilOriginal[i];
	}
}

/**
* Constructor de copia de PagSubdivisionProfile
*/
PagSubdivisionProfile::PagSubdivisionProfile(const PagSubdivisionProfile & orig) {
	*this = orig;
}

/**
 * Operador igual de PagSubdivisionProfile
 */
void PagSubdivisionProfile::operator=(const PagSubdivisionProfile & orig) {
	numPuntosPerfilOriginal = orig.numPuntosPerfilOriginal;
	numPuntosPerfilSubdividido = orig.numPuntosPerfilSubdividido;
	numDivisiones = orig.numDivisiones;

	if(orig.perfilOriginal != nullptr) {
		perfilOriginal = new PuntosPerfil[numPuntosPerfilOriginal];
		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			perfilOriginal[i] = orig.perfilOriginal[i];
		}
	}
	else perfilOriginal = nullptr;


	if(orig.perfilSubdividido != nullptr) {
		perfilSubdividido = new PuntosPerfil[numPuntosPerfilSubdividido];
		for (int i = 0; i < numPuntosPerfilSubdividido; i++) {
			perfilSubdividido[i] = orig.perfilSubdividido[i];
		}
	}
	else perfilSubdividido = nullptr;
	
}

/**
 * Funcion encargada de subdividir el perfil de revolucion
 */
void PagSubdivisionProfile::subdivisionPolilineas() {
	if (numPuntosPerfilOriginal > 2 && numDivisiones > 0) {

		int numPuntos = numPuntosPerfilOriginal;
		int expectedNumberOfPoints = (2 * numPuntos) - 1;
		PuntosPerfil* perfiltemporal;

		for (int j = 0; j < numDivisiones; j++) {
			perfiltemporal = new PuntosPerfil[expectedNumberOfPoints];
			perfiltemporal[0] = perfilSubdividido[0];
			perfiltemporal[expectedNumberOfPoints - 1] = perfilSubdividido[numPuntos - 1];
			for (int i = 1; i < numPuntos - 1; i++) {

				PuntosPerfil h1;
				h1.x = (perfilSubdividido[i - 1].x + perfilSubdividido[i].x) / 2;
				h1.y = (perfilSubdividido[i - 1].y + perfilSubdividido[i].y) / 2;

				PuntosPerfil h2;
				h2.x = (perfilSubdividido[i].x + perfilSubdividido[i + 1].x) / 2;
				h2.y = (perfilSubdividido[i].y + perfilSubdividido[i + 1].y) / 2;

				PuntosPerfil pi;
				pi.x = ((perfilSubdividido[i].x / 2) + (h1.x / 4) + (h2.x / 4));
				pi.y = ((perfilSubdividido[i].y / 2) + (h1.y / 4) + (h2.y / 4));

				perfiltemporal[(i * 2) - 1] = h1;
				perfiltemporal[i * 2] = pi;
				if (i == numPuntos - 2)perfiltemporal[(i * 2) + 1] = h2;

			}
			numPuntos = expectedNumberOfPoints;
			perfilSubdividido = perfiltemporal;
			expectedNumberOfPoints = (2 * expectedNumberOfPoints) - 1;

			numPuntosPerfilSubdividido = numPuntos;
		}
	}
}

/**
 * Destructor de PagSubdivisionProfile
 */
PagSubdivisionProfile::~PagSubdivisionProfile() {
	if (perfilOriginal != nullptr) delete[] perfilOriginal;
	if (perfilSubdividido != nullptr) delete[] perfilSubdividido;
}
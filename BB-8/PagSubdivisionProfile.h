#pragma once

#include "Structs.h"

using namespace Structs;

class PagSubdivisionProfile{
	PuntosPerfil* perfilOriginal;
	PuntosPerfil* perfilSubdividido;
	int numDivisiones;
	int numPuntosPerfilOriginal;
	int numPuntosPerfilSubdividido;
public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil *_perfilOriginal);
	PagSubdivisionProfile(const PagSubdivisionProfile &orig);
	void operator = (const PagSubdivisionProfile &orig);
	void subdivisionPolilineas();
	PuntosPerfil& getPerfil() const { return *perfilSubdividido; }
	int getNumPuntosPerfil() const { return numPuntosPerfilSubdividido; }
	~PagSubdivisionProfile();
};


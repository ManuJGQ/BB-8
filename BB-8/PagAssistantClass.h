#pragma once

#include "PagRevolutionObject.h"

class PagAssistantClass{
public:
	PagAssistantClass();
	PagRevolutionObject leerDatos(Structs::Fichero _fichero) const;
	static void devolverDatos(const PagRevolutionObject &orig);
	~PagAssistantClass();
};


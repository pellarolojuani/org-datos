/*
 * Buscador.h
 *
 *  Created on: Jun 15, 2013
 *      Author: lucia
 */

#ifndef BUSCADOR_H_
#define BUSCADOR_H_
#include "../Parser/Parser.h"
#include "../structures/abb/ArbolB.h"
#include "../structures/abb/Nodo.h"
#include "../NombresArchivos.h"
#include <iostream>

namespace buscador {

class Buscador {
public:
	Buscador();

	abb::Nodo buscarTermino(string term);



	virtual ~Buscador();
private:
	FILE* archivoLexico;
	FILE* tablalexico;
	abb::ArbolB<abb::Nodo, ORDEN_NODO>* arbolB;
	void levantarArbol();
};

} /* namespace buscador */
#endif /* BUSCADOR_H_ */

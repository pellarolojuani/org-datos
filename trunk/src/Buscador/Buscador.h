/*
 * Buscador.h
 *
 *  Created on: Jun 15, 2013
 *      Author: lucia
 */

#ifndef BUSCADOR_H_
#define BUSCADOR_H_
#include "../Parser/Parser.h"
#include "../Parser/ParserDirectorio.h"
#include "../structures/abb/ArbolB.h"
#include "../structures/abb/Nodo.h"
#include "../NombresArchivos.h"
#include "Match.h"
#include <iostream>

namespace buscador {

class Buscador {
public:
	Buscador();

	abb::Nodo buscarTermino(string term);
	match::Match* buscarFrase(string frase);


	string* parsearLinea(char* line);
	string toString(char c);

	bool poseeDocumento(abb::Nodo nodo, int documento);
	bool esDocumentoCandidato(abb::Nodo* nodosEncontrados, int cantidadNodos, int documento);


	bool esPalabraSiguiente(abb::Nodo n1, abb::Nodo n2, int doc);
	bool estanTodasLasPalabras(abb::Nodo* nodosEncontrados, string* palabras, int cantidadPalabras);

	int getPosPalabraEnVectorPosiciones(abb::Nodo n1, int doc, int* frecuenciaADevolver);

	abb::ArbolB<abb::Nodo, ORDEN_NODO>* arbolB;


	virtual ~Buscador();
private:
	FILE* archivoLexico;
	FILE* tablalexico;
	FILE* archivoPunteros;
	FILE* archivoPosiciones;

	void levantarArbol();

};

} /* namespace buscador */
#endif /* BUSCADOR_H_ */

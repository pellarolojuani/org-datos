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





	virtual ~Buscador();
private:
	FILE* archivoLexico;
	FILE* tablalexico;
	FILE* archivoPunteros;
	FILE* archivoPosiciones;
	string* parsearLinea(char* line);
	string toString(char c);

	bool poseeDocumento(abb::Nodo nodo, int documento);
	bool esDocumentoCandidato(abb::Nodo* nodosEncontrados, int cantidadNodos, int documento);

	bool esFrase(abb::Nodo* ns, int cantidad, int doc);
	bool esPalabraSiguiente(abb::Nodo n1, abb::Nodo n2, int doc, int* ultimaPos);
	bool estanTodasLasPalabras(abb::Nodo* nodosEncontrados, string* palabras, int cantidadPalabras);

	int getPosPalabraEnVectorPosiciones(abb::Nodo n1, int doc, int* frecuenciaADevolver);

	Posiciones getPosiciones(abb::Nodo n, int doc);

	parser::Posiciones getUbicacionFrases(parser::Posiciones pos1, parser::Posiciones pos2);


	abb::ArbolB<abb::Nodo, ORDEN_NODO>* arbolB;

	void levantarArbol();

};

} /* namespace buscador */
#endif /* BUSCADOR_H_ */

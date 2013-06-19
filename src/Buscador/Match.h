/*
 * Match.h
 *
 *  Created on: Jun 18, 2013
 *      Author: lucia
 */

#ifndef MATCH_H_
#define MATCH_H_

#include <string>
#include <iostream>
#include "../Parser/Posiciones.h"
#include "../NombresArchivos.h"
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
using namespace std;
namespace match {

class Match {
public:
	Match();
	virtual ~Match();
	string* getDocumentos();
	void setOffsetsDocumentos(parser::Posiciones* offsetsDocumentos);
	void setEncontroFrase(bool encontro);
	bool encontroFrase();
	void agregarMatch(int doc);
	int getCantidadMatches();
	void borrar();

private:
	string* documentos;
	FILE* archivoDirectorios;
	parser::Posiciones* offsetsDocumentos;
	bool fraseExiste;
	int cantidadMatches;
};

} /* namespace abb */
#endif /* MATCH_H_ */

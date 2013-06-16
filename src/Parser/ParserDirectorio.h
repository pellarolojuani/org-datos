/*
 * ParserDirectorio.h
 *
 *  Created on: Jun 7, 2013
 *      Author: lucia
 */

#ifndef PARSERDIRECTORIO_H_
#define PARSERDIRECTORIO_H_
#include "Parser.h"
#include "../structures/abb/ArbolB.h"
#include "../structures/abb/Nodo.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>



namespace parser {

class ParserDirectorio {
public:
	ParserDirectorio();
	ParserDirectorio(char* nombreDirectorio);

	void parsearDirectorio();

	virtual ~ParserDirectorio();
private:
	Parser* parser;
	char* nombreDirectorio;
	FILE* archivoDirectorios;
	FILE* archivoPunteros;

	FILE* archivoLexicoFC;
	FILE* tablaLexicoFC;
	bool isCurrOrParentDir(const string& name);
	void parseFile(FILE* archivo, int offsetFile);

	void parsearDirectorioRec(char* directorioRuta);

	//Aca es donde ocurre la magia
	abb::ArbolB<abb::Nodo, ORDEN_NODO>* arbolito;

	void almacenarLexico();
};

} /* namespace parser */
#endif /* PARSERDIRECTORIO_H_ */

/*
 * ParserDirectorio.h
 *
 *  Created on: Jun 7, 2013
 *      Author: lucia
 */

#ifndef PARSERDIRECTORIO_H_
#define PARSERDIRECTORIO_H_
#include "Parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#ifndef LONG_MAX_LINEA
#define LONG_MAX_LINEA 1024
#endif

namespace parser {

class ParserDirectorio {
public:
	ParserDirectorio();
	ParserDirectorio(char* nombreDirectorio);
	//Esta funcion va a ir parseando los directorios, a su vez deberá crear un archivo con
	//sus respectivos nombres, y con las palabras que parsee las deberá ir metiendo en el trie,
	//indicando su posición en en texto.
	int parsearDirectorio();


	virtual ~ParserDirectorio();
private:
	Parser* parser;
	char* nombreDirectorio;
	FILE* archivoDirectorios;
	FILE* archivoPunteros;
};

} /* namespace parser */
#endif /* PARSERDIRECTORIO_H_ */

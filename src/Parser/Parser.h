/*
 * Parser.h
 *
 *  Created on: Apr 2, 2013
 *      Author: lucia
 */


#ifndef DELIMITADORES
#define DELIMITADORES ",.;: ¡!¿?\"\n<>()-_”[]'\n"
#endif /*DELIMITADORES*/

#ifndef MAX_POSICIONES_LINEA
#define MAX_POSICIONES_LINEA 200
#endif /* MAX_POSICIONES */

#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Posiciones.h"

using namespace std;

namespace parser {

class Parser {
public:
	Parser();
	string* parsearLinea(string, Posiciones* posiciones);
	int getUltimaPosicion();
	void resetUltimaPosicion();
	virtual ~Parser();

private:
	string delimitadores;
	bool esDelimitador(char c, string* delimitadores);
	void agregarPalabra(string palabra, string* palabras, int cantPalabras);
	string tolowercase(string s);
	int pos;
};

} /* namespace parser */
#endif /* PARSER_H_ */

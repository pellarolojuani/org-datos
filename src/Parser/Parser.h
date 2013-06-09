/*
 * Parser.h
 *
 *  Created on: Apr 2, 2013
 *      Author: lucia
 */


#ifndef DELIMITADORES
#define DELIMITADORES ",.;: ¡!¿?\"\n<>"
#endif /*DELIMITADORES*/

#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <stdio.h>
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
	int pos;
};

} /* namespace parser */
#endif /* PARSER_H_ */

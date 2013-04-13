/*
 * Parser.h
 *
 *  Created on: Apr 2, 2013
 *      Author: lucia
 */


#ifndef DELIMITADORES
#define DELIMITADORES ",.;: ¡!¿?\""
#endif /*DELIMITADORES*/

#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
using namespace std;

namespace parser {

class Parser {
public:
	Parser();
	string* parsearLinea(string);
	virtual ~Parser();

private:
	string delimitadores;
	bool esDelimitador(char c, string* delimitadores);

};

} /* namespace parser */
#endif /* PARSER_H_ */

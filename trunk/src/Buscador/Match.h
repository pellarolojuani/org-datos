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

using namespace std;
namespace abb {

class Match {
public:
	Match();
	virtual ~Match();
	string* getDocumentos();

private:
	string* documentos;
	FILE* archivoDirectorios;
	parser::Posiciones offsetsDocumentos;
};

} /* namespace abb */
#endif /* MATCH_H_ */

/*
 * PersistorPunteros.h
 *
 *  Created on: Jun 16, 2013
 *      Author: lucia
 */

#include "../Parser/Posiciones.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#ifndef PERSISTORPUNTEROS_H_
#define PERSISTORPUNTEROS_H_
using namespace std;
namespace punteros {

//TODO
//VERSION BASICA PARA ENTREGAR EN LA REVISION
class PersistorPunteros {
public:
	PersistorPunteros(FILE* archivoPunteros, FILE* archivoPosiciones);
	void persistirDistancias(parser::Posiciones* docs, parser::Posiciones* posRelativas);
	int getOffsetPunteros();
	int getOffsetPosiciones();
	virtual ~PersistorPunteros();
private:
	FILE* archivoPunteros;
	FILE* archivoPosiciones;
	int offsetPunteros;
	int offsetPosiciones;

};

} /* namespace abb */
#endif /* PERSISTORPUNTEROS_H_ */

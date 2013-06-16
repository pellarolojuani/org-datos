/*
 * Nodo.h
 *
 *  Created on: Jun 13, 2013
 *      Author: lucia
 */

#ifndef NODO_H_
#define NODO_H_
#include "../../Parser/Posiciones.h"
#ifndef ORDEN_NODO
#define ORDEN_NODO 40
#endif
#include <iostream>
using namespace std;
using namespace parser;

namespace abb {
class Nodo {
public:
	Nodo();
	virtual ~Nodo();

	string getPalabra();
	Posiciones* getPosiciones();
	int getOffsetPosiciones();
	void setOffsetPosiciones(int offsetPosiciones);
	void setPosiciones(Posiciones* posiciones);
	void setPalabra(string palabra);
	int getFrecuencia();
	void setFrecuencia(int frecuencia);

	Posiciones* getOffsetsDocumentos();
	void setOffsetsDocumentos(Posiciones* offsts);

	bool operator==(Nodo&);//compara a igual
	bool operator<(Nodo&);//compara a menor
	bool operator>(Nodo&);//compara a mayor
	bool operator=(Nodo);//asigna
private:
	Posiciones* posiciones;
	Posiciones* offsetsDocumentos;
	int frecuencia;
	string palabra;
	int offsetPosiciones;
	int offsetPunteros;

};

} /* namespace abb */
#endif /* NODO_H_ */

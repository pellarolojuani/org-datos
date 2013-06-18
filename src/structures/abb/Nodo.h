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
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace parser;

namespace abb {
class Nodo {
public:
	Nodo();
	virtual ~Nodo();

	string getPalabra();

	Posiciones* getPosiciones();
	void setPosiciones(Posiciones* posiciones);

	Posiciones* getDocumentos();
	void setDocumentos(Posiciones* posiciones);

	Posiciones* getFrecuencias();
	void setFrecuencias(Posiciones* frecuencias);

	void setPalabra(string palabra);
	int getFrecuencia();
	void setFrecuencia(int frecuencia);

	void setLineaTabla(long int l);
	long int getLineaTabla();

	bool fueEncontrado();
	void setEncontrado(bool encontrado);



	bool operator==(Nodo&);//compara a igual
	bool operator<(Nodo&);//compara a menor
	bool operator>(Nodo&);//compara a mayor
	bool operator=(Nodo);//asigna
private:
	Posiciones* posiciones;
	Posiciones* documentos;
	Posiciones* frecuencias;
	int frecuencia;
	string palabra;
	int offsetPosiciones;
	int offsetPunteros;
	long int lineaTabla;
	bool encontrado;

};

} /* namespace abb */
#endif /* NODO_H_ */

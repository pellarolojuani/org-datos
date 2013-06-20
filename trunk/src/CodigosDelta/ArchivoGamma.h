/*
 * ArchivoGamma.h
 *
 *  Created on: 19/06/2013
 *      Author: matias
 */

#ifndef ARCHIVOGAMMA_H_
#define ARCHIVOGAMMA_H_

#include <fstream>
#include <vector>
#include "CodigoGamma.h"

class ArchivoGamma {
public:
	ArchivoGamma();
	virtual ~ArchivoGamma();
	/**
	 * Parametros: vector a persistir
	 * Devuelve: posicion donde empieza
	 */
	int guardarVector(std::vector<unsigned int> vector);
	/**
	 * Parametros: puntero de la lista a llenar, posicion
	 * devuelve largo de la lista
	 */
	std::vector<unsigned int> levantarVector(int posicion);
	/**
	 * Seteo la posicion en el archivo
	 */
	void setPosicion(long posicion);
private:
	std::fstream file;
	CodigoGamma gamma;
};

#endif /* ARCHIVOGAMMA_H_ */

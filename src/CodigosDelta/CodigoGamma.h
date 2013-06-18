/*
 * CodigoGamma.h
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#ifndef CODIGOGAMMA_H_
#define CODIGOGAMMA_H_

class CodigoGamma {
public:
	CodigoGamma();
	/**
	 * Devuelve el largo en bits
	 */
	int codificar(unsigned int numero, char*& destino);
	int decodificar(char* cadena);
	virtual ~CodigoGamma();
};

#endif /* CODIGOGAMMA_H_ */

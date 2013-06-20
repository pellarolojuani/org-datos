/*
 * ListaGamma.h
 *
 *  Created on: 19/06/2013
 *      Author: matias
 */

#ifndef LISTAGAMMA_H_
#define LISTAGAMMA_H_

class ListaGamma {
public:
	ListaGamma();
	virtual ~ListaGamma();
	void agregarNumero(int numero);
	char* obtenerLista();
};

#endif /* LISTAGAMMA_H_ */

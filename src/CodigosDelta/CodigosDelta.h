/*
 * CodigosDelta.h
 *
 *  Created on: Jun 8, 2013
 *      Author: lucia
 */

#ifndef CODIGOSDELTA_H_
#define CODIGOSDELTA_H_

namespace parser {

class CodigosDelta {
public:
	CodigosDelta();
	void codificar(char* fuente, char* destino);
	void decodificar(char* fuente, char* destino);
	virtual ~CodigosDelta();
};

} /* namespace parser */
#endif /* CODIGOSDELTA_H_ */

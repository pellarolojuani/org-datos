/*
 * NombresArchivos.h
 *
 *  Created on: Jun 15, 2013
 *      Author: lucia
 */

#ifndef NOMBRESARCHIVOS_H_
#define NOMBRESARCHIVOS_H_



namespace constantes {

class NombresArchivos {
public:
	NombresArchivos();
	static const char* archivoDirectorios;
	static const char* archivoPunteros;
	static const char* archivoLexico;
	static const char* archivoTablaLexico;
	static const char* archivoPosicionesRelativas;
	static const char* archivoGamma;
	virtual ~NombresArchivos();
};


} /* namespace buscador */
#endif /* NOMBRESARCHIVOS_H_ */


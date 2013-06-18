/*
 * BitWriter.h
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#ifndef BITWRITER_H_
#define BITWRITER_H_

class BitWriter {
public:
	BitWriter();
	virtual ~BitWriter();
	void crearBuffer(int size);
	//Asegurarse de poner un 1 o un 0, por las dudas
	void grabarBit(bool bit);
	char* obtenerCadena();
private:
	char* cadena;
	unsigned int posicion;
	unsigned char mask;
};

#endif /* BITWRITER_H_ */

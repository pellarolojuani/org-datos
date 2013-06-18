/*
 * BitReader.h
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#ifndef BITREADER_H_
#define BITREADER_H_

class BitReader {
public:
	BitReader();
	virtual ~BitReader();
	void cargarCadena(char* cadena, int largo);
	bool leerBit();
private:
	char* cadena;
	unsigned int largo;
	unsigned int offset;
	unsigned char mask;
};

#endif /* BITREADER_H_ */

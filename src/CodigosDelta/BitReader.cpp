/*
 * BitReader.cpp
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#include "BitReader.h"

BitReader::BitReader() {
}

BitReader::~BitReader() {
}

void BitReader::cargarCadena(char* cadena, int largo) {
	this->offset = 0;
	this->cadena = cadena;
	this->largo = largo;
	this->mask = 1;
}

bool BitReader::leerBit() {
	bool result = 0;
	if(offset < (largo << 3)){ //<< es como hacer *8
		char aux = cadena[offset >> 3]; // >> 3 es como hacer /8
		//And entre bits de la mascara y el char
		if ((aux & mask) != 0){
			result = 1;
		}
		//Voy rotando la mascara
		this->mask = this->mask << 1 | this->mask >> 7;
		offset++;
	}
	return result;
}



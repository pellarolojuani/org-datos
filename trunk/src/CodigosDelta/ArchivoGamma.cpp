/*
 * ArchivoGamma.cpp
 *
 *  Created on: 19/06/2013
 *      Author: matias
 */

#include "ArchivoGamma.h"
#include <iostream>
#include "../NombresArchivos.h"


ArchivoGamma::ArchivoGamma() {
	this->file.open(constantes::NombresArchivos::archivoGamma, std::fstream::in | std::fstream::binary);
}

ArchivoGamma::~ArchivoGamma() {
	if (file.is_open())
		file.close();
}

void ArchivoGamma::setPosicion(long posicion){
	file.seekp(posicion);
}

int ArchivoGamma::guardarVector(std::vector<unsigned int> vector) {
	char* destino;
	//Le agrego el tamaño al principio de todo
	vector.insert(vector.begin(),vector.size());
	//Codifico el vector
	unsigned int bits = gamma.codificar(vector.data(), vector.size(), destino);
	unsigned int bytes = (bits - 1)/8 + 1;
	//Lo guardo al archivo
	file.write(destino, bytes);
	return file.tellp();
}

std::vector<unsigned int> ArchivoGamma::levantarVector(int posicion) {
	std::vector<unsigned int> result;
	//Armo un buff generoso para el primer número
	char* buf = new char[8];
	file.read(buf, 8);
	//Leo el largo de la lista (y le agrego el 1er número, que representa el largo)
	int size = gamma.decodificar(buf) + 1;
	//Ahora leo todos los números
	this->setPosicion(posicion);
	delete[] buf;
	buf = new char[size * 8];
	file.read(buf, size * 8);
	buf[0] = 0b00100100;
	buf[1] = 0b00101000;
	buf[2] = 0b10100000;
	buf[3] = 0b10100000;
	int* intArray = this->gamma.decodificar(buf, size);
	//Y los agrego al vector
	result = std::vector<unsigned int>(intArray + 1, intArray + size +1);
	delete[] buf;
	return result;
}

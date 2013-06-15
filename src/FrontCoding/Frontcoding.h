/*
 * Frontcoding.h
 *
 *  Created on: Jun 14, 2013
 *      Author: lucia
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>

#ifndef FRONTCODING_H_
#define FRONTCODING_H_
using namespace std;
namespace frontcoding {

class Frontcoding {
public:

	Frontcoding(FILE* nombreArchivoLexico, FILE* nombreArchivoTabla );

	string compararPorCharDistintos(string uno, string dos, int* cantidad);
	int guardarEnArchivo(string str, int charsDistintos, int offset);

	void agregarPalabra(string palabra);

	void almacenarLexico();
	virtual ~Frontcoding();
private:
	FILE* archIntlexico;
	FILE* archIntTabla;
	FILE* archIntLexicoTemp;
	FILE* archIntTablaTemp;
	string palabraAnterior;
	int offset;

};

} /* namespace frontcoding */
#endif /* FRONTCODING_H_ */

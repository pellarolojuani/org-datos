/*
 * CodigoGamma.cpp
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#include "CodigoGamma.h"
#include "BitWriter.h"
#include "BitReader.h"

CodigoGamma::CodigoGamma() {
	// TODO Auto-generated constructor stub

}

int CodigoGamma::codificar(unsigned int numero, char*& destino) {
	//Saco el tamaño del binario
	BitWriter writer;
	writer.crearBuffer(16);
	int binSize = 0;
	unsigned int mask = 1;
	unsigned int aux = numero;
	while (aux != 0) {
		aux = aux >> 1;
		mask = mask << 1;
		binSize++;
	}
	//Corrijo mascara (queda corrida 1 a la izquierda)
	mask = mask >> 1;
	//Inicio el writer
	writer.crearBuffer(16);
	//Grabo ceros (tamaño num binario -1)
	for (int i = 1; i < binSize; i++) {
		writer.grabarBit(0);
	}
	for (int i = 0; i < binSize; i++) {
		bool bit = ((numero & mask) != 0);
		mask = mask >> 1;
		writer.grabarBit(bit);
	}

	destino = writer.obtenerCadena();
	//devuelvo el largo del codigo gamma
	int result = (binSize * 2) - 1;
	return result;
}

int CodigoGamma::decodificar(char* cadena) {
	BitReader reader;
	int result = 1;
	//Asumo gammas de menos de 16 bytes... si, es cualquiera, pero es un buffer válido
	//En realidad el límite está para no extenderse al infinito y hacer un potencial NPE
	reader.cargarCadena(cadena, 16);
	char contadorCeros = 0;
	//Leo la primer mitad del código
	while (reader.leerBit() != 1) {
		contadorCeros++;
	}
	//Dado a que 1 es el único de 1 solo bit, y el 2 ya tiene 3 bits
	if (contadorCeros > 0) {
		//Ahora leo la parte en binario
		char contadorBinario;
		for (contadorBinario = 0; contadorBinario < contadorCeros;
				contadorBinario++) {
			//Voy agrgando bit por bit
			result = (result << 1) | reader.leerBit();
		}
	}
	return result;
}

CodigoGamma::~CodigoGamma() {
	// TODO Auto-generated destructor stub
}


/*
 * CodigoGamma.cpp
 *
 *  Created on: 17/06/2013
 *      Author: matias
 */

#include "CodigoGamma.h"
#include "BitReader.h"

CodigoGamma::CodigoGamma() {
	// TODO Auto-generated constructor stub

}

int CodigoGamma::codificar(unsigned int numero, char* destino) {
	//Saco el tamaño del binario
	char binSize = 0;
	unsigned int aux = numero;
	while (aux != 0){
		aux = aux >> 1;
		binSize++;
	}

}

int CodigoGamma::decodificar(char* cadena) {
	BitReader reader;
	int result = 1;
	//Asumo gammas de menos de 16 bytes... si, es cualquiera, pero es un buffer válido
	//En realidad el límite está para no extenderse al infinito y hacer un potencial NPE
	reader.cargarCadena(cadena, 16);
	char contadorCeros = 0;
	//Leo la primer mitad del código
	while (reader.leerBit() != 1){
		contadorCeros++;
	}
	//Dado a que 1 es el único de 1 solo bit, y el 2 ya tiene 3 bits
	if(contadorCeros > 0){
		//Ahora leo la parte en binario
		char contadorBinario;
		for (contadorBinario = 0; contadorBinario < contadorCeros; contadorBinario++){
			//Voy agrgando bit por bit
			result = (result << 1) | reader.leerBit() ;
		}
	}
	return result;
}

CodigoGamma::~CodigoGamma() {
	// TODO Auto-generated destructor stub
}


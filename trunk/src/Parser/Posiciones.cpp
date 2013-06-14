/*
 * Posiciones.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: lucia
 */

#include "Posiciones.h"

namespace parser {

Posiciones::Posiciones() {
	this->cantPosiciones = 0;
	this->posiciones = new int[MAX_POSICIONES];
	this->tamanio = MAX_POSICIONES;

}

int* Posiciones::getPosiciones(){
	return posiciones;
}

void Posiciones::setCantPosiciones(int cant){
	this->cantPosiciones = cant;
}

int Posiciones::getCantPosiciones(){
	return this->cantPosiciones;
}

void Posiciones::resetCantidadPosiciones(){
	cantPosiciones = 0;
}

void Posiciones::agregarPosicion(int nueva){

	if (this->cantPosiciones >= this->tamanio){
		//Si necesito más posiciones entonces tengo que agrandar el vector posiciones.
		tamanio = this->cantPosiciones*2;
		int* nuevasp = new int[this->cantPosiciones*2];
		for(int i = 0; i< this->getCantPosiciones(); i++){
			nuevasp[i] = this->posiciones[i];
		}
		nuevasp[this->cantPosiciones] = nueva;
		this->posiciones = nuevasp;
		this->cantPosiciones++;
	} else {
		this->posiciones[this->cantPosiciones] = nueva;
		this->cantPosiciones++;
	}

}

Posiciones::~Posiciones() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

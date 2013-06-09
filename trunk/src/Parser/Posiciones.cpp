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

Posiciones::~Posiciones() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

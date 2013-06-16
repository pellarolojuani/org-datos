/*
 * Nodo.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: lucia
 */

#include "Nodo.h"

namespace abb {

Nodo::Nodo() {
	// TODO Auto-generated constructor stub

}

string Nodo::getPalabra(){
	return this->palabra;
}

Posiciones* Nodo::getOffsetsDocumentos(){
	return this->offsetsDocumentos;
}

void Nodo::setOffsetsDocumentos(Posiciones* offsts){
	this->offsetsDocumentos = offsts;
}

void Nodo::setPalabra(string palabra){
	this->palabra = palabra;
}

Posiciones* Nodo::getPosiciones(){
	return this->posiciones;
}

void Nodo::setPosiciones(Posiciones* posiciones){
	this->posiciones = posiciones;
}

int Nodo::getFrecuencia(){
	return this->frecuencia;
}
void Nodo::setFrecuencia(int frecuencia){
	this->frecuencia = frecuencia;
}

int Nodo::getOffsetPosiciones(){
	return offsetPosiciones;
}
void Nodo::setOffsetPosiciones(int offsetPosiciones){
	this->offsetPosiciones = offsetPosiciones;
}

bool Nodo::operator==(Nodo& nuevoFF)
{
	bool sonIguales = (nuevoFF.getPalabra() == this->getPalabra());
	return sonIguales;
}

bool Nodo::operator<(Nodo& nuevoFF)
{
	bool soyMenor = (this->getPalabra() < nuevoFF.getPalabra());
	return soyMenor;
}
bool Nodo::operator>(Nodo& nuevoFF)
{
	bool soyMayor = (this->getPalabra() > nuevoFF.getPalabra());
	return soyMayor;
}

bool Nodo::operator=(Nodo nuevoFF)
{
	this->frecuencia = nuevoFF.getFrecuencia();
	this->posiciones = nuevoFF.getPosiciones();
	this->palabra = nuevoFF.getPalabra();
}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}

} /* namespace abb */

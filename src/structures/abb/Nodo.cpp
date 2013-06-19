/*
 * Nodo.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: lucia
 */

#include "Nodo.h"

namespace abb {

Nodo::Nodo() {
	documentos = NULL;
	posiciones = NULL;
	frecuencias = NULL;
	frecuencia = 0;
	offsetPosiciones = 0;
	offsetPunteros = 0;
	lineaTabla=0;

}

string Nodo::getPalabra(){
	return this->palabra;
}

Posiciones* Nodo::getDocumentos(){
	return this->documentos;
}

void Nodo::setDocumentos(Posiciones* posiciones){
	this->documentos = posiciones;
}

bool Nodo::fueEncontrado(){
	return this->encontrado;
}

void Nodo::setEncontrado(bool encontrado){
	this->encontrado = encontrado;
}

void Nodo::setLineaTabla(long int l){
	this->lineaTabla = l;
}

long int Nodo::getLineaTabla(){
	return lineaTabla;
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

Posiciones* Nodo::getFrecuencias(){
	return this->frecuencias;
}

void Nodo::setFrecuencias(Posiciones* frecuencias){
	this->frecuencias = frecuencias;
}

int Nodo::getFrecuencia(){
	return this->frecuencia;
}
void Nodo::setFrecuencia(int frecuencia){
	this->frecuencia = frecuencia;
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
	this->documentos = nuevoFF.getDocumentos();
	this->frecuencias = nuevoFF.getFrecuencias();
	this->lineaTabla = nuevoFF.getLineaTabla();
	this->palabra = nuevoFF.getPalabra();
	this->encontrado = nuevoFF.fueEncontrado();

	return true;
}

void Nodo::borrar(){
	delete(posiciones);
	delete(documentos);
	delete(frecuencias);
}

Nodo::~Nodo() {

}

} /* namespace abb */

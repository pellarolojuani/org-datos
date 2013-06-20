/*
 * Nodo.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: lucia
 */

#include "Nodo.h"

namespace abb {

void agregarDocumentos(std::vector<int>& vector, Posiciones* documentos);
void agregarPosiciones(std::vector<int>& vector, Posiciones* posiciones);

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

std::vector<int> Nodo::serializarPosiciones() {
	//PRE: asumo que frecuencia me da el tamaño de la lista documentos y de posiciones
	std::vector<int> result;
	agregarDocumentos(result, this->documentos);
	agregarPosiciones(result, this->posiciones);
	return result;
}

void Nodo::deserializarPosiciones(std::vector<int> data) {
	//Acá con el primer valor se cuantos pares hay (documento; frecuencia)
	//a ese número lo multiplico por 2 y me dice dónde están las posiciones
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

/**
 * Serializo los documentos
 */
void agregarDocumentos(std::vector<int>& vector, Posiciones* documentos){
	vector.empty();
	int cantidad = documentos->getCantPosiciones();
	int* posiciones = documentos->getPosiciones();
	int i = 0;
	int docActual;
	int docsDistintos = 0;
	if (cantidad > 0){
		docActual = posiciones[i];
		//reservo un lugar para decir cuantos pares distintos hay
		vector.push_back(0);
		//Agrupo documentos iguales, la lista pasa a ser pares de (cantidad, número)
		while (i < cantidad){
			docsDistintos++;
			int contador = 0;
			while (docActual == posiciones [i]){
				contador++;
				i++;
			}
			vector.push_back(contador);
			vector.push_back(docActual);
			docActual = posiciones[i];
		}
	}
	vector[0] = docsDistintos;
}

void agregarPosiciones(std::vector<int>& vector, Posiciones* posiciones){
	int* arrPosiciones = posiciones->getPosiciones();
	for (int i=0; i < posiciones->getCantPosiciones(); i++){
		vector.push_back(arrPosiciones[i]);
	}
}

} /* namespace abb */

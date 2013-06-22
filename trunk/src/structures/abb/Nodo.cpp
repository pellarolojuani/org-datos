/*
 * Nodo.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: lucia
 */

#include "Nodo.h"

namespace abb {

void agregarDistancias(std::vector<unsigned int>& vector, Posiciones* documentos, Posiciones* posicionesRelativas);

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

std::vector<unsigned int> Nodo::serializarPosiciones() {
	//PRE: asumo que frecuencia me da el tamaño de la lista documentos y de posiciones
	std::vector<unsigned int> result;
	agregarDistancias(result, this->documentos, this->posiciones);
	std::cout<<"Elementos del vector a serializar: "<<std::endl;
	for(int i=0; i<result.size(); i++){
		std::cout<<result.at(i)<<"   ";

	}
	std::cout<<std::endl;
	return result;
}

void Nodo::deserializarPosiciones(std::vector<unsigned int> data) {
	//Acá con el primer valor se cuantos pares hay (documento; frecuencia)
	//a ese número lo multiplico por 2 y me dice dónde están las posiciones

	std::cout<<"Elementos del vector a deserializar: "<<std::endl;
	for(int i=0; i<data.size(); i++){
		std::cout<<data.at(i)<<"   ";

	}
	std::cout<<std::endl;

	int cantParesDocFrec = data.at(0);
	int comienzoPosiciones = cantParesDocFrec*2+1;
	this->documentos = new Posiciones();
	this->frecuencias = new Posiciones();
	this->posiciones = new Posiciones();

	int itPosiciones=comienzoPosiciones;
	int sumaDocAnterior=0;
	for( int i=1; i<cantParesDocFrec; i+=2 ){
		int doc = data.at(i+1);
		this->documentos->agregarPosicion(doc+sumaDocAnterior);
		int frec = data.at(i);
		this->frecuencias->agregarPosicion(frec);
		int sumaPosAnterior=0;
		while(itPosiciones<frec){
			//Voy agregando posiciones
			this->posiciones->agregarPosicion(data.at(itPosiciones)+sumaPosAnterior);
			itPosiciones++;
			sumaPosAnterior+=data.at(itPosiciones);
		}
		sumaDocAnterior+=doc;

	}
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
void agregarDistancias(std::vector<unsigned int>& vector, Posiciones* documentos, Posiciones* posicionesRelativas){
	vector.clear();
	int cantidad = documentos->getCantPosiciones();
	int* posiciones = documentos->getPosiciones();
	int i = 0;
	int docActual=0;
	int docsDistintos = 0;
	int docAnterior = 0;
	std::vector<unsigned int> frecuenciasParciales;

	if (cantidad > 0){
		//Doc actual es la distancia al anterior.
		docActual = posiciones[i];
		//reservo un lugar para decir cuantos pares distintos hay
		vector.push_back(0);

		//Agrupo documentos iguales, la lista pasa a ser pares de (cantidad, número)
		while (i < cantidad){

			docsDistintos++;
			int contador = 0;
			while ((docActual == posiciones[i]) && i<documentos->getCantPosiciones()){
				//Las frecuencias las tengo que almacenar aca tambien porque si uso distancias puede quedar mocho.
				int* arrPosiciones = posicionesRelativas->getPosiciones();
				int distanciaTermino;
				if(contador==0){
					distanciaTermino = arrPosiciones[i];
				} else
					distanciaTermino = arrPosiciones[i]-arrPosiciones[i-1];

				//La posicion que agrego es la distancia a la anterior.
				frecuenciasParciales.push_back(distanciaTermino);

				contador++;
				i++;
				docAnterior = docActual;

			}

			int distanciaDocumento;
			if(docActual==docAnterior){
				distanciaDocumento = docActual;
			} else
				distanciaDocumento = docActual-docAnterior;

			vector.push_back(contador);
			vector.push_back(distanciaDocumento);
			docAnterior = docActual;
			docActual = posiciones[i];
		}
	}
	//Finalmente agrego todas las frecuencias
	for(int i=0; i<frecuenciasParciales.size();i++){
		vector.push_back(frecuenciasParciales.at(i));

	}
	vector[0] = docsDistintos;
}

} /* namespace abb */

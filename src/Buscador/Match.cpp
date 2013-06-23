/*
 * Match.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: lucia
 */

#include "Match.h"

#ifndef MAX_MATCHES
#define MAX_MATCHES 50
#endif

namespace match {

Match::Match() {
	this->archivoDirectorios = fopen(constantes::NombresArchivos::archivoDirectorios,"rb");
	documentos = NULL;
	fraseExiste = false;
	cantidadMatches = 0;
}

string* Match::getDocumentos(){

	string* docNames = new string[MAX_MATCHES];
	for(int i = 0; i<this->offsetsDocumentos->getCantPosiciones(); i++){
		docNames[i]=descifrarDoc(this->offsetsDocumentos->getPosiciones()[i]);
	}
	return docNames;

}

string Match::descifrarDoc(int doc){
	//Obtengo el offset del docu.
	fseek(archivoDirectorios,0,SEEK_SET);
	int n=1;
	//Offset me dice desde donde leo el string del doc.
	int offset=0;

	while(n<doc){
		char c = fgetc(archivoDirectorios);
		offset++;
		//Tengo que leer n comas hasta llegar al docu.
		while(c!=','){
			c = fgetc(archivoDirectorios);
			offset++;
		}
		n++;
	}

	fseek(archivoDirectorios,offset,SEEK_SET);
	char c = fgetc(archivoDirectorios);
	string docName;
	while(c!=','){
		stringstream s0;
		string lineaStr;
		s0 << c;
		s0 >> lineaStr;
		docName.append(lineaStr);
		c=fgetc(this->archivoDirectorios);
	}

	return docName;
}

void Match::setOffsetsDocumentos(parser::Posiciones* offsetsDocumentos){
	this->offsetsDocumentos = offsetsDocumentos;
}

void Match::agregarMatch(int doc){
	this->offsetsDocumentos->agregarPosicion(doc);
}

int Match::getCantidadMatches(){
	return this->offsetsDocumentos->getCantPosiciones();
}

bool Match::encontroFrase(){
	return this->fraseExiste;
}

void Match::setEncontroFrase(bool encontro){
	this->fraseExiste = encontro;
}

void Match::borrar(){
	delete(this->offsetsDocumentos);
}

Match::~Match() {
	// TODO Auto-generated destructor stub
}

} /* namespace abb */

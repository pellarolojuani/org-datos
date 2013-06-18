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
	offsetsDocumentos = NULL;
}

string* Match::getDocumentos(){

	string* docNames = new string[MAX_MATCHES];
	for(int i = 0; i<this->offsetsDocumentos->getCantPosiciones(); i++){
		fseek(archivoDirectorios,offsetsDocumentos->getPosiciones()[i],SEEK_SET);
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
		docNames[i] =  docName;
		cout<<docName<<endl;
	}
	return docNames;

}

void Match::setOffsetsDocumentos(parser::Posiciones* offsetsDocumentos){
	this->offsetsDocumentos = offsetsDocumentos;
}

void Match::agregarMatch(int doc){
//	this->offsetsDocumentos->agregarPosicion(doc);
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

Match::~Match() {
	// TODO Auto-generated destructor stub
}

} /* namespace abb */

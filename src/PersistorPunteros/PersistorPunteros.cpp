/*
 * PersistorPunteros.cpp
 *
 *  Created on: Jun 16, 2013
 *      Author: lucia
 */

#include "PersistorPunteros.h"


namespace punteros {

PersistorPunteros::PersistorPunteros(FILE* archivoPunteros, FILE* archivoPosiciones) {
	this->archivoPosiciones = archivoPosiciones;
	this->archivoPunteros = archivoPunteros;
	this->offsetPosiciones = 0;
	this->offsetPunteros = 0;

}

int PersistorPunteros::getOffsetPunteros(){
	return this->offsetPunteros;

}
int PersistorPunteros::getOffsetPosiciones(){
	return this->offsetPosiciones;
}

void PersistorPunteros::persistirDistanciasComprimidas(parser::Posiciones* docs, parser::Posiciones* posRelativas){

	for(int i=0; i<docs->getCantPosiciones(); i++){
		//PARA CADA DOCUMENTO CALCULO LA DISTANCIA Y LA COMPRIMO EN GAMMA

		int doc = docs->getPosiciones()[i];
		int docAct = doc;
		int distancia=doc;
		if(i!=0){
			distancia = doc - docs->getPosiciones()[i-1];
		}

	}


}
void PersistorPunteros::persistirDistancias(parser::Posiciones* docs, parser::Posiciones* posRelativas){

	int i=0;
	int j=0;

	while(i<docs->getCantPosiciones()){

		int doc = docs->getPosiciones()[i];
		int docAct = doc;

		int distancia=doc;
		if(i!=0){
			distancia = doc - docs->getPosiciones()[i-1];
		}

		//Guardo el documento.
		stringstream s3;
		s3 << distancia;
		string strDoc = s3.str();
		strDoc.append(",");

		fputs(strDoc.c_str(), this->archivoPunteros);

		int frecuencia=0;
		int posUltima = 0;

		int c=0;
		while(docAct == doc && j<posRelativas->getCantPosiciones()){

			posUltima = posRelativas->getPosiciones()[j];

			int distanciaTerm = posUltima;
			if(c!=0){
				distanciaTerm = posUltima - posRelativas->getPosiciones()[j-1];
			}
			c=1;
			j++;
			stringstream s2;
			s2 << distanciaTerm;
			string distanciaTermStr = s2.str();
//			distanciaTermStr.append(",");
			fputs(distanciaTermStr.c_str(), this->archivoPosiciones);

//			this->offsetPosiciones+=distanciaTermStr.length();

			i++;
			docAct = docs->getPosiciones()[i];


			frecuencia++;
		}


		this->offsetPosiciones=ftell(this->archivoPosiciones);
		stringstream s4;
		s4 << frecuencia;
		string strFrec= s4.str();
//		strFrec.append(",");
		fputs(strFrec.c_str(), this->archivoPunteros);
		this->offsetPunteros=ftell(this->archivoPunteros);

	}
}

PersistorPunteros::~PersistorPunteros() {
	// TODO Auto-generated destructor stub
}

} /* namespace abb */

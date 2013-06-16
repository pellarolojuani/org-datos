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

void PersistorPunteros::persistirDistancias(parser::Posiciones docs, parser::Posiciones posRelativas){
	for(int i = 0; i<docs.getCantPosiciones(); i++){
		int frel;
		while (docs.getPosiciones()[i] == docs.getPosiciones()[i+1]){
			frel++;
			i++;
		}
		//ESCRIBO "frecuencia relativa, documento" por un lado.
		stringstream ss;
		ss << frel;
		string strFrelativa = ss.str();

		stringstream s1;
		s1 << docs.getPosiciones()[i];
		string strDoc = s1.str();

		string linea = strDoc.append(",").append(strFrelativa).append(",");
		fputs(linea.c_str(), this->archivoPunteros);


		//LUEGO LAS POSICIONES EN EL ARCHIVO DE POSICIONES.
		for(int j=0; j<frel; j++){
			stringstream s2;
			s2 << posRelativas.getPosiciones()[i];
			string strPosRelativa = s2.str();
			strPosRelativa.append(",");
			fputs(strPosRelativa.c_str(), this->archivoPosiciones);

		}


		i++;
	}
}

PersistorPunteros::~PersistorPunteros() {
	// TODO Auto-generated destructor stub
}

} /* namespace abb */

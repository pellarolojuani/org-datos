/*
 * StringMatch.cpp
 *
 *  Created on: 01/04/2013
 *      Author: matias
 */

#include "StringMatch.h"
#include <string>

void StringMatch::agregarUbicacion(int ubicacion) {
	this->ubicaciones.push_back(ubicacion);
}

char* StringMatch::getStringUbicaciones() {
	//acá deberían convertirse a gamma y encadenarse
	/*std::string str = "";
	unsigned int i;
	for (i = 0; i < this->ubicaciones.size(); i++){
		str += ubicaciones[i];
	}
	//Copio el string a un char[]
	char* result = new char[str.length() +1];
	str.copy(result,str.length(), 0);*/
	char* result = new char[ubicaciones.size()];
	unsigned int i;
	for (i = 0; i < this->ubicaciones.size(); i++){
			result[i] = (char) ubicaciones[i];
	}
	return result;
}

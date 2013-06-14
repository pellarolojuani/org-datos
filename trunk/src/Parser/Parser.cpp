/*
 * Parser.cpp
 *
 *  Created on: Apr 2, 2013
 *      Author: lucia
 */

#include "Parser.h"

namespace parser {

Parser::Parser() {
	this->delimitadores = DELIMITADORES;
	pos = 0;

}

//Funcion que parsea una linea de entrada devolviendo un vector de strings.
//Recibe como parámetro un elemento posiciones, donde se va a guardar la posicion
//relativa de cada string (se mapean uno a uno)
string*  Parser::parsearLinea(string str, Posiciones* posicionesFinales){

	//esta linea es cualquiera, pero después veremos qué va pasando
	//con las palabras que se agreguen al parser, o sea, capaz que hay
	//que meter la palabra parseada en un nodo de arbol B, o un arbol binario
	//o algo así.
	string* arrayPalabras=new string[MAX_POSICIONES_LINEA];

	//Proceso caracter a caracter y voy formando palabras.
	string palabra = "";
	unsigned int i = 0;
	unsigned int indiceComienzoPalabra = 0;
	unsigned int indicePalabra = 0;


	while ( i < str.length() ){
		char caracter = str.at(i);

		if (this->esDelimitador(caracter,&delimitadores)){
			string palabra = str.substr(indiceComienzoPalabra, (i-indiceComienzoPalabra));
			i++;


			posicionesFinales->agregarPosicion(pos-(i-indiceComienzoPalabra-1));


			indiceComienzoPalabra=i;
			//Se encontró una palabra.

			arrayPalabras[indicePalabra] = tolowercase(palabra);
			indicePalabra++;

			bool esCaracterFinal = false;
			if(i < str.length()){
				caracter=str.at(i);
			} else
				esCaracterFinal = true;

			//Si llego a tener varios delimitadores seguidos, por ejemplo "; " los escapeo.
			while((this->esDelimitador(caracter,&delimitadores)&&!esCaracterFinal)){
				i++;
				indiceComienzoPalabra=i;
				if(i < str.length()){
					caracter=str.at(i);
				} else
					esCaracterFinal = true;
			}

		} else if (i == str.length()-1) {
			string palabra = str.substr(indiceComienzoPalabra, (i-indiceComienzoPalabra)+1);

			arrayPalabras[indicePalabra] = tolowercase(palabra);

			posicionesFinales->agregarPosicion(pos);


			indicePalabra++;
			i++;
		}

		else
			i++;
		pos++;

	}

	return arrayPalabras;

}

bool Parser::esDelimitador(char c, string* delimitadores){
	for(unsigned int i = 0; i < delimitadores->length(); i++){
		if (delimitadores->at(i) == c){
			return true;
		}
	}
	return false;

}

int Parser::getUltimaPosicion(){
	return this->pos;
}

void Parser::resetUltimaPosicion(){
	this->pos=0;
}

string Parser::tolowercase(string s){
	for (int i=0;i<strlen(s.c_str());i++){
		if (s[i] >= 0x41 && s[i] <= 0x5A)
			s[i] = s[i] + 0x20;
	}
	return s;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

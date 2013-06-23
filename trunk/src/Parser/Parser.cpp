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
	numeroPalabra = 1;

}

//Funcion que parsea una linea de entrada devolviendo un vector de strings.
//Recibe como parámetro un elemento posiciones, donde se va a guardar la posicion
//relativa de cada string (se mapean uno a uno)
string*  Parser::parsearLinea(string str, Posiciones* posicionesFinales, int maxPosicionesLinea){

	//esta linea es cualquiera, pero después veremos qué va pasando
	//con las palabras que se agreguen al parser, o sea, capaz que hay
	//que meter la palabra parseada en un nodo de arbol B, o un arbol binario
	//o algo así.
	string* arrayPalabras=new string[maxPosicionesLinea];

	//Proceso caracter a caracter y voy formando palabras.
	string palabra = "";
	unsigned int i = 0;
	unsigned int indiceComienzoPalabra = 0;
	unsigned int indicePalabra = 0;

	while ( i < str.length() ){
		char caracter = str.at(i);

		if ((this->esDelimitador(caracter,&delimitadores))&&(i!=0)){

			string palabra;

			palabra = str.substr(indiceComienzoPalabra, (i-indiceComienzoPalabra));

			i++;

			//MODIFICO A: ahora en vez de la posicion de una palabra, te dice el numero de dicha palabra en el texto
			//cosa que al buscar por frase sea mas facil determinar si dos palabras van seguidas.
//			posicionesFinales->agregarPosicion(pos-(i-indiceComienzoPalabra-1));
			posicionesFinales->agregarPosicion(numeroPalabra);

			indiceComienzoPalabra=i;
			//Se encontró una palabra.
			numeroPalabra++;

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

		} else if ((this->esDelimitador(caracter,&delimitadores))&&(i == 0)){
			bool esCaracterFinal = false;
			while((this->esDelimitador(caracter,&delimitadores)&&!esCaracterFinal)){
				i++;
				indiceComienzoPalabra=i;
				if(i < str.length()){
					caracter=str.at(i);
				} else
					esCaracterFinal = true;
			}
		}

		else if (i == str.length()-1) {
			string palabra = str.substr(indiceComienzoPalabra);
			palabra=quitarFinDeLinea(palabra);
			arrayPalabras[indicePalabra] = tolowercase(palabra);
			numeroPalabra++;

			posicionesFinales->agregarPosicion(numeroPalabra);


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
	//Determino si es una letra mediante codigo ascii.

	if (((c >= 97) && (c <= 122)) ||((c >= 65) && (c <= 90)) ||( c == 195 ) ||
//			(c == 161) || (c == 129)|| (c == 169) ||
//			(c == 137) || (c == 173)|| (c == 141) || (c == 47) ||
			(c == 179) || (c == 147)|| (c == 186) || (c == 154) || (c == 177)|| (c == 145)){

			return false ;

		} else {
			if( (c > 47) && (c <= 57)){
				return false ;
			}
		}

		return true ;
//	for(unsigned int i = 0; i < delimitadores->length(); i++){
//		if (delimitadores->at(i) == c){
//			return true;
//		}
//	}
//	return false;

}

int Parser::getUltimaPosicion(){
	return this->pos;
}

void Parser::resetUltimaPosicion(){
	this->pos=0;
	this->numeroPalabra=1;
}

string Parser::quitarFinDeLinea(string s){
	if (s[strlen(s.c_str())-1] == '\n')
		s = s.substr(0,strlen(s.c_str()));
	return s;
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

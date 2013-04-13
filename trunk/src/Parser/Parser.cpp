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

}

//Funcion que parsea una linea de entrada devolviendo un vector de strings.
string*  Parser::parsearLinea(string str){

	//esta linea es cualquiera, pero después veremos qué va pasando
	//con las palabras que se agreguen al parser, o sea, capaz que hay
	//que meter la palabra parseada en un nodo de arbol B, o un arbol binario
	//o algo así.
	string* arrayPalabras=new string[50];

	//Proceso caracter a caracter y voy formando palabras.
	string palabra = "";
	unsigned int i = 0;
	unsigned int indiceComienzoPalabra = 0;
	unsigned int indicePalabra = 0;

	while ( i < str.length() ){
		char caracter = str.at(i);
		if (this->esDelimitador(caracter,&delimitadores)){
			string palabra = str.substr(indiceComienzoPalabra, (i-indiceComienzoPalabra));
			cout<<palabra<<endl;
			i++;
			indiceComienzoPalabra=i;
			//Se encontró una palabra.
			arrayPalabras[indicePalabra] = palabra;
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
			arrayPalabras[indicePalabra] = palabra;
			cout<<palabra<<endl;
			indicePalabra++;
			i++;
		}

		else
			i++;

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


Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

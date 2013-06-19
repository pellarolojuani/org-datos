//============================================================================
// Name        : Datos.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "Parser/Parser.h"
#include "Parser/ParserDirectorio.h"
#include "Parser/Posiciones.h"
#include "FrontCoding/Frontcoding.h"
#include "structures/abb/Nodo.h"
#include "structures/abb/ArbolB.h"
#include "CodigosDelta/BitReader.h"
#include "CodigosDelta/CodigoGamma.h"
#include "Buscador/Buscador.h"

#ifndef LONG_MAX_STRING_BUSQUEDA
#define LONG_MAX_STRING_BUSQUEDA 500
#endif

using namespace std;
void testBitReader();
void testGamma();

int main(int argc, char* argv[]) {

	//Parametro -i arma el indice.
  	if((strcmp(argv[1],"-i")==0)){
  		char* textos = argv[2];
  		parser::ParserDirectorio pars(textos);
  		pars.parsearDirectorio();
  	//Parametro -r busca las frases
  	}else if((strcmp(argv[1],"-r")==0)){
		buscador::Buscador *busq = new buscador::Buscador();
		string b = argv[2];
		match::Match* match = busq->buscarFrase(b);
		string* docs = match->getDocumentos();
		for (int i=0; i<match->getCantidadMatches(); i++){
			cout<<docs[i]<<endl;
		}

		if(match->getCantidadMatches() == 0){
			cout<<"Ningún documento contiene la frase buscada."<<endl;
		}
	} else
		cout<<"USAGE: ./Datos -<i,r> <directorio,frase>"<<endl;

//	char* textos = "/home/lucia/miau";
//	parser::ParserDirectorio pars(textos);
//	pars.parsearDirectorio();

//	buscador::Buscador busq;;
//	string b = "into my bosom";
//	match::Match* match = busq.buscarFrase(b);
//	string* docs = match->getDocumentos();
//	for (int i=0; i<match->getCantidadMatches(); i++){
//		cout<<docs[i]<<endl;
//	}





//	testBitReader();
//	testBitReader();
//	testGamma();

	//Esta linea es la cabala oficial.
//	cout << "Goodbye matrix, hello world!" << endl;
//	busq.borrar();
	return 0;
}





void testBitReader(){
	BitReader reader;
	char prueba[] = {5, 126};
	reader.cargarCadena(prueba, 2);
	for (int i=0; i<16; i++){
		cout<<"Bit : " << i << "valor : " << reader.leerBit() << endl;;
	}
}



void testGamma(){
	CodigoGamma gamma;
	char* cadena;
	int size = gamma.codificar(45, cadena);
	BitReader reader;
	reader.cargarCadena(cadena, (size / 8) + 1);
	for (int i=0; i<size; i++){
		cout<<"Bit : " << i << "valor : " << reader.leerBit() << endl;;
	}
}

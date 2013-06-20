//============================================================================
// Name        : Datos.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "Parser/Parser.h"
#include "Parser/ParserDirectorio.h"
#include "Parser/Posiciones.h"
#include "FrontCoding/Frontcoding.h"
#include "structures/abb/Nodo.h"
#include "structures/abb/ArbolB.h"
#include "CodigosDelta/BitReader.h"
#include "CodigosDelta/ArchivoGamma.h"
#include "Buscador/Buscador.h"

#ifndef LONG_MAX_STRING_BUSQUEDA
#define LONG_MAX_STRING_BUSQUEDA 500
#endif

using namespace std;
void testArchivoGamma();

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
  	testArchivoGamma();
	//Esta linea es la cabala oficial.
	cout << "Goodbye matrix, hello world!" << endl;
	return 0;
}

void testArchivoGamma(){
	ArchivoGamma gammaFile;
	unsigned int numeros[] = {1120, 123440, 212312350, 112330};
	vector<unsigned int> vec(numeros, numeros + 4);
	vector<unsigned int> vec2;
	gammaFile.guardarVector(vec);
	gammaFile.cerrar();
	gammaFile.abrir();
	vec2 = gammaFile.levantarVector(0);
	for (int i = 0 ; i< vec2.size(); i++)
			cout << vec2[i] << endl;
}

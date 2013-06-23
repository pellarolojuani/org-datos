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
void testSerializar();

int main(int argc, char* argv[]) {
	//Parametro -i arma el indice.
//	testSerializar();
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
		
//	char* textos = "/home/lucia/new";
//	parser::ParserDirectorio pars(textos);
//	pars.parsearDirectorio();
//
//	buscador::Buscador busq;;
//	string b = "a ver";
//	match::Match* match = busq.buscarFrase(b);
//	string* docs = match->getDocumentos();
//	for (int i=0; i<match->getCantidadMatches(); i++){
//		cout<<docs[i]<<endl;
//	}
//	//Esta linea es la cabala oficial.
	cout << "Goodbye matrix, hello world!" << endl;
//	return 0;
}

void testSerializar(){
	cout<<"Prueba serializar" <<endl;
	abb::Nodo n;
	n.setPalabra("hola");
	Posiciones* posPruebasDocs = new Posiciones();
	posPruebasDocs->agregarPosicion(1);
	posPruebasDocs->agregarPosicion(1);
	posPruebasDocs->agregarPosicion(2);
	posPruebasDocs->agregarPosicion(2);

	Posiciones* posPruebasFrec = new Posiciones();
	posPruebasFrec->agregarPosicion(1);
	posPruebasFrec->agregarPosicion(2);
	posPruebasFrec->agregarPosicion(3);
	posPruebasFrec->agregarPosicion(4);


	n.setDocumentos(posPruebasDocs);
	n.setPosiciones(posPruebasFrec);
	vector<unsigned int> vecPrueba = n.serializarPosiciones();
	ArchivoGamma gammaFile;
	int offsetZ = gammaFile.guardarVector(vecPrueba);


	std::vector<unsigned int> vecto = gammaFile.levantarVector(offsetZ);
	cout<<"Ahora levanto: " << offsetZ<< endl;
	cout<<vecto.size()<<endl;
	for(int i=0; i<vecto.size();i++){
		cout<<vecto.at(i)<<" ";
	}
	cout<<endl;
}


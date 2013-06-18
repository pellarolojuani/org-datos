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

using namespace std;
void testParsearLinea();
void testNodo();
void testAbb();
void testFrontCoding();
void testBitReader();
void testGamma();
abb::Nodo setNodo(int);

int main() {

	char* textos = "/home/lucia/new";
/*	testParsearLinea();
//	parser::ParserDirectorio pars(textos);
//	pars.parsearDirectorio();


	buscador::Buscador *busq = new buscador::Buscador();
	abb::Nodo n = busq->buscarTermino("reginald");

	cout<<"POSICIONES:   ";
	for (int h=0; h<n.getPosiciones()->getCantPosiciones(); h++){
		cout<<n.getPosiciones()->getPosiciones()[h]<<",";
	}
	cout<<endl;

	cout<<"DOCS:  ";
	for (int l=0; l<n.getDocumentos()->getCantPosiciones(); l++){
		cout<<n.getDocumentos()->getPosiciones()[l]<<",";
	}
	cout<<endl;

	n = busq->buscarTermino("routh");
	cout<<"POSICIONES:   ";
	for (int h=0; h<n.getPosiciones()->getCantPosiciones(); h++){
		cout<<n.getPosiciones()->getPosiciones()[h]<<",";
	}
	cout<<endl;

	cout<<"DOCS:  ";
	for (int l=0; l<n.getDocumentos()->getCantPosiciones(); l++){
		cout<<n.getDocumentos()->getPosiciones()[l]<<",";
	}
	cout<<endl;
*/


//	testNodo();
//
//	testAbb();

//	testFrontCoding();

//	abb::Nodo n;
//	cout<<"FREC:  "<<n.getFrecuencia()<<endl;
//	n = busq->buscarTermino("cinco");

//
//	cout<<n.getPalabra()<<endl;
//	cout<<"FREC:  "<<n.getFrecuencia()<<endl;

//	testBitReader();
	testGamma();

	cout << "Goodbye matrix, hello world!" << endl;
	return 0;
}


abb::Nodo setNodo(int j){
	abb::Nodo nodo;
	string str = "       zarazaa zab za za fiuu&      ";
	parser::Parser pars;
	parser::Posiciones poss;
	string* test = pars.parsearLinea(str, &poss);

	nodo.setFrecuencia(45);
	nodo.setPalabra(test[j]);

	nodo.setPosiciones(&poss);

	return nodo;

}

void testAbb(){
	abb::ArbolB<abb::Nodo, 3> arbolito;

	abb::Nodo nodo1 = setNodo(1);
	abb::Nodo nodo2 = setNodo(2);
	abb::Nodo nodo3 = setNodo(3);
	abb::Nodo nodo4 = setNodo(4);
	abb::Nodo nodo5 = setNodo(5);

	arbolito.insertar(nodo1);
	arbolito.insertar(nodo2);
	arbolito.insertar(nodo3);
	arbolito.insertar(nodo4);
	arbolito.insertar(nodo5);


	abb::Nodo nodoAReemplazar;
	nodoAReemplazar.setFrecuencia(1);
	nodoAReemplazar.setPalabra("uno");

	abb::Nodo nodoBusq = setNodo(1);
	nodoBusq.setPalabra("uno");
	nodoBusq.setFrecuencia(4);

	abb::Nodo nodoRespuesta;


//	Posiciones posNodoAReempl;
//	posNodoAReempl.agregarPosicion(67);
//	posNodoAReempl.agregarPosicion(6);
//	posNodoAReempl.agregarPosicion(7);
//	nodoAReemplazar.setPosiciones(posNodoAReempl);
//
//	Posiciones posNodoBusq;
//	posNodoBusq.agregarPosicion(1);
//	posNodoBusq.agregarPosicion(2);
//	posNodoBusq.agregarPosicion(3);
//	nodoBusq.setPosiciones(posNodoBusq);
//
//	cout<<"Posiciones: ";
//	for (int i = 0; i<nodoAReemplazar.getPosiciones().getCantPosiciones(); i++) {
//		cout<<nodoAReemplazar.getPosiciones().getPosiciones()[i]<<" , ";
//	}
//
//	arbolito.insertar(nodoAReemplazar);
//	arbolito.modify(nodoBusq);
//
//	nodoRespuesta = arbolito.buscarYdevolver(nodoBusq);
//
//	nodoBusq = arbolito.buscarYdevolver(nodo3);
//	cout<<nodo3.getFrecuencia()<<endl;
//
//	cout<<"Posiciones: ";
//	for (int i = 0; i<nodoRespuesta.getPosiciones().getCantPosiciones(); i++) {
//		cout<<nodoRespuesta.getPosiciones().getPosiciones()[i]<<" , ";
//	}
//	cout<<endl;




	arbolito.emitir();


}

void testNodo(){
	abb::Nodo nodo;
	abb::Nodo nodo2;

	string str = "       zarazaa zab za za fiuu& palabras palabras y mas palabras zazaza      ";
	parser::Parser pars;
	int posiciones[20];
	int i;
	parser::Posiciones* poss = new Posiciones();
	string* test = pars.parsearLinea(str, poss);

	nodo.setFrecuencia(1);
	nodo.setPalabra(test[1]);
	nodo.setPosiciones(poss);

	nodo2.setFrecuencia(1);
	nodo2.setPalabra(test[2]);
	nodo2.setPosiciones(poss);

	cout<<nodo.getPalabra()<<endl;
	cout<<nodo.getFrecuencia()<<endl;

	cout<<nodo2.getPalabra()<<endl;
	cout<<nodo2.getFrecuencia()<<endl;

	cout<<"Test igual igual (son distintos)"<<endl;
	cout<<(nodo2==nodo)<<endl;

	cout<<"Test mayor"<<endl;
	cout<<(nodo2<nodo)<<endl;

	cout<<"Test menor"<<endl;
	cout<<(nodo2>nodo)<<endl;

	nodo = nodo2;
	cout<<nodo.getPalabra()<<endl;
	cout<<nodo.getFrecuencia()<<endl;

	cout<<"Test igual igual (da que son iguales)"<<endl;
	cout<<(nodo2==nodo)<<endl;
}

void testParsearLinea(){
	//Pruebas parser
	string str = "12,1 tres cuatro cinco seis   ;y sigo probando porque soy re jevi re jodida";
	parser::Parser pars;
	int i;

	parser::Posiciones poss;

	string* test = pars.parsearLinea(str, &poss);

	cout<<"cant poss:"<<poss.getCantPosiciones()<<endl;

	for (int i = 0; i<poss.getCantPosiciones(); i++) {
		cout<<"Palabra: "<<test[i]<<" en la posicion "<<poss.getPosiciones()[i]<<endl;
	}
//
//	string uno= " So,\" he commented, \"they learn wisdom and come to be head men. But why \"";
//	parser::Posiciones poss2;
//	test = pars.parsearLinea(uno, &poss2);
//	string* test2 = pars.parsearLinea(uno, &poss2);
//	for (int i = 0; i<poss.getCantPosiciones(); i++) {
//		cout<<"Palabra: "<<test2[i]<<" en la posicion "<<poss2.getPosiciones()[i]<<endl;
//	}


//	string dos = "have you come, Strong Father, with so many canoes? Do you build a new";
//	pars.parsearLinea(dos);
//	string tres= "post? Or do you fight the French Hearts?\" The French Hearts was his name";
//	pars.parsearLinea(tres);
//	string cuatro= "for the Nor\'westers.";
//	pars.parsearLinea(cuatro);
//	string cinco = "";
//	pars.parsearLinea(cinco);
//	string seis="\"Neither,\" answered Dunvegan. \"The Factor sent me many moons ago to";
//	pars.parsearLinea(seis);
//	string siete= "find his daughter and to bring her back to the Fort.";
//	pars.parsearLinea(siete);
}

void testFrontCoding(){
	FILE* we = NULL;
	frontcoding::Frontcoding FC(we,we);
	string a = "a";
	string aab = "aab";
	string casa = "casa";
	string casita = "casita";

	int cant;
	string dist = FC.compararPorCharDistintos(a,aab,&cant);
	cout<<dist<<" "<<cant<<endl;;

	dist = FC.compararPorCharDistintos(aab,casa,&cant);
	cout<<"aab casa "<<dist<<" "<<cant<<endl;

	dist = FC.compararPorCharDistintos(casa,casita,&cant);
	cout<<"casa casita "<<dist<<" "<<cant<<endl;

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

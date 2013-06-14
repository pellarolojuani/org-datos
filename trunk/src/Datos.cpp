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

using namespace std;
void testParsearLinea();
void testNodo();
void testAbb();
void testFrontCoding();
abb::Nodo setNodo(int);

int main() {

	char* textos = "/home/lucia/test";
//	testParsearLinea();
	parser::ParserDirectorio pars(textos);
	pars.parsearDirectorio();

//	testNodo();
//
//	testAbb();

//	testFrontCoding();

	cout << "Goodbye matrix, hello world!" << endl;
	return 0;
}

abb::Nodo setNodo(int j){
	abb::Nodo nodo;
	string str = "       zarazaa zab za za fiuu&      ";
	parser::Parser pars;
	parser::Posiciones poss;
	string* test = pars.parsearLinea(str, &poss);

	nodo.setFrecuencia(1);
	nodo.setPalabra(test[j]);
	nodo.setOffsetPosiciones(4);
	nodo.setPosiciones(poss);

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

	abb::Nodo nodoBusq = setNodo(1);
	nodoBusq.setPalabra("za");
//	nodoBusq.setFrecuencia(232323);
//
//	bool modif = arbolito.modify(nodoBusq);
//
//	abb::Nodo nodoVacio;
//	nodoVacio=arbolito.buscarYdevolver(nodoBusq);
//
//	cout<<nodoVacio.getPalabra()<<endl;
//
//
	nodoBusq.setFrecuencia(4);

	bool encontrado = arbolito.buscar(nodoBusq);
	cout<<nodoBusq.getFrecuencia()<<endl;

	if(encontrado) cout<<"fue encontrado"<<endl;
	else cout<<"no fue encontrado"<<endl;




	cout<<"Anda por favor arbolito querido"<<endl;
	arbolito.emitir();


}

void testNodo(){
	abb::Nodo nodo;
	abb::Nodo nodo2;

	string str = "       zarazaa zab za za fiuu& palabras palabras y mas palabras zazaza      ";
	parser::Parser pars;
	int posiciones[20];
	int i;
	parser::Posiciones poss;
	string* test = pars.parsearLinea(str, &poss);

	nodo.setFrecuencia(1);
	nodo.setPalabra(test[1]);
	nodo.setOffsetPosiciones(4);
	nodo.setPosiciones(poss);

	nodo2.setFrecuencia(1);
	nodo2.setPalabra(test[2]);
	nodo2.setOffsetPosiciones(4);
	nodo2.setPosiciones(poss);

	cout<<nodo.getPalabra()<<endl;
	cout<<nodo.getFrecuencia()<<endl;
	cout<<nodo.getOffsetPosiciones()<<endl;

	cout<<nodo2.getPalabra()<<endl;
	cout<<nodo2.getFrecuencia()<<endl;
	cout<<nodo2.getOffsetPosiciones()<<endl;

	cout<<"Test igual igual (son distintos)"<<endl;
	cout<<(nodo2==nodo)<<endl;

	cout<<"Test mayor"<<endl;
	cout<<(nodo2<nodo)<<endl;

	cout<<"Test menor"<<endl;
	cout<<(nodo2>nodo)<<endl;

	nodo = nodo2;
	cout<<nodo.getPalabra()<<endl;
	cout<<nodo.getFrecuencia()<<endl;
	cout<<nodo.getOffsetPosiciones()<<endl;

	cout<<"Test igual igual (da que son iguales)"<<endl;
	cout<<(nodo2==nodo)<<endl;
}

void testParsearLinea(){
	//Pruebas parser
	string str = "         sdasdas dsfdsfhdskk dsafaskds ahdskfhadsfh dashkkadsf dskk    ";
	parser::Parser pars;
	int i;

	parser::Posiciones poss;

	string* test = pars.parsearLinea(str, &poss);

	cout<<"cant poss:"<<poss.getCantPosiciones()<<endl;

	for (int i = 0; i<poss.getCantPosiciones(); i++) {
		cout<<"Palabra: "<<test[i]<<" en la posicion "<<poss.getPosiciones()[i]<<endl;
	}

	string uno= " So,\" he commented, \"they learn wisdom and come to be head men. But why \"";
	parser::Posiciones poss2;
	test = pars.parsearLinea(uno, &poss2);
	string* test2 = pars.parsearLinea(uno, &poss2);
	for (int i = 0; i<poss.getCantPosiciones(); i++) {
		cout<<"Palabra: "<<test2[i]<<" en la posicion "<<poss2.getPosiciones()[i]<<endl;
	}


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
	cout<<"aab casa"<<dist<<" "<<cant<<endl;

	dist = FC.compararPorCharDistintos(casa,casita,&cant);
	cout<<"casa casita"<<dist<<" "<<cant<<endl;

}



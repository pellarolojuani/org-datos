//============================================================================
// Name        : Datos.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "text/StringMatch.h"
#include "test/structures/TrieNodeTest.h"
#include <stdio.h>
#include "Parser/Parser.h"
using namespace std;

int main() {
	cute::ide_listener listener;
	TrieNodeTest trieNodeTest;
	cute::makeRunner(listener)(trieNodeTest.testSuite(), "TrieNode tests");

	//Pruebas parser
	string str = "Goodbye matrix, hello world";
	parser::Parser pars;
	string* test = pars.parsearLinea(str);
	cout<<test<<endl;

	string uno= "\"So,\" he commented, \"they learn wisdom and come to be head men. But why";
	pars.parsearLinea(uno);
	string dos = "have you come, Strong Father, with so many canoes? Do you build a new";
	pars.parsearLinea(dos);
	string tres= "post? Or do you fight the French Hearts?\" The French Hearts was his name";
	pars.parsearLinea(tres);
	string cuatro= "for the Nor\'westers.";
	pars.parsearLinea(cuatro);
	string cinco = "";
	pars.parsearLinea(cinco);
	string seis="\"Neither,\" answered Dunvegan. \"The Factor sent me many moons ago to";
	pars.parsearLinea(seis);
	string siete= "find his daughter and to bring her back to the Fort.";
	pars.parsearLinea(siete);


	cout << "Goodbye matrix, hello world!" << endl;
	return 0;
}

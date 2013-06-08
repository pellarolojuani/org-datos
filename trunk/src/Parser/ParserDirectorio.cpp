/*
 * ParserDirectorio.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: lucia
 */

#include "ParserDirectorio.h"

namespace parser {

ParserDirectorio::ParserDirectorio(char* nombreDirectorio) {
	this->nombreDirectorio = nombreDirectorio;
	this->parser = new Parser();
	this->archivoDirectorios = fopen("/home/lucia/directorios.dat","w");
	this->archivoPunteros = fopen("/home/lucia/punteros.dat","w");

}

int ParserDirectorio::parsearDirectorio(){

	DIR *dip;
	struct dirent *dit;

	if ((dip = opendir(this->nombreDirectorio)) == NULL)
	{
		cout<<"El directorio "<<dit->d_name<<" no pudo a abrirse."<<endl;
		return -1;
	}

	int i;
	while ((dit = readdir(dip)) != NULL)
	{
		//Por cada archivo leido
		parser->resetUltimaPosicion();

		cout<<dit->d_name<<endl;
		char ruta[1024]="";
		cout<<this->nombreDirectorio;
		strcat(ruta, this->nombreDirectorio);
		strcat(ruta, "/");
		strcat(ruta, dit->d_name);

		//Paso a abrir el directorio y parsearlo linea por linea
		FILE* dirAct = fopen(ruta, "r");
		int longitud_maxima_linea = 1024;
		char linea[LONG_MAX_LINEA];
		while (fgets(linea, LONG_MAX_LINEA, dirAct) != NULL)
		      printf("%s", linea);
		i++;


	}

}



ParserDirectorio::~ParserDirectorio() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

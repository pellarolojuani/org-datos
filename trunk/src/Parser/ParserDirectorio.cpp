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

	//TODO esto después cambiarlo
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
	int offset=0;
	while ((dit = readdir(dip)) != NULL)
	{
		//Por cada archivo leido
		parser->resetUltimaPosicion();

		char* nombreDirectorio = dit->d_name;
		char ruta[1024]="";

		strcat(ruta, this->nombreDirectorio);
		strcat(ruta, "/");
		strcat(ruta, nombreDirectorio);
		FILE* dirAct = fopen(ruta, "r");

		//Guardo el nombre del archivo en archivoDirectorios.
		fputs(nombreDirectorio, this->archivoDirectorios);

		//TODO variable a codificar en gamma (sería el archivo donde aparece)
		cout<<nombreDirectorio<<offset<<endl;
		offset+= strlen(nombreDirectorio);

		//Paso a abrir el directorio y parsearlo linea por linea

		int longitud_maxima_linea = 1024;
		char linea[LONG_MAX_LINEA];

		while (fgets(linea, LONG_MAX_LINEA, dirAct) != NULL){

			Posiciones posis;
		    string* parseo = this->parser->parsearLinea(linea,&posis);

		    cout<<"Entonces, para la línea "<<linea<<"tenemos:"<<endl;

		    for (int i = 0; i<posis.getCantPosiciones(); i++) {
		    	cout<<"Palabra: "<<parseo[i]<<" en la posicion "<<posis.getPosiciones()[i]<<endl;
		    }

		}
		i++;


	}

}



ParserDirectorio::~ParserDirectorio() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

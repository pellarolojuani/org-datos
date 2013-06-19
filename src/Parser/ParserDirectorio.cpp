/*
 * ParserDirectorio.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: lucia
 */

#include "ParserDirectorio.h"
#include "../structures/abb/ArbolB.h"
#include "../structures/abb/Nodo.h"
#include "../FrontCoding/Frontcoding.h"
#include "../NombresArchivos.h"
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string>


static const string CURR_DIR_STR = ".";
static const string PARENT_DIR_STR = "..";

namespace parser {

ParserDirectorio::ParserDirectorio(char* nombreDirectorio) {
	this->nombreDirectorio = nombreDirectorio;
	this->parser = new Parser();

	arbolito = new abb::ArbolB<abb::Nodo, ORDEN_NODO>;

	this->archivoDirectorios = fopen(constantes::NombresArchivos::archivoDirectorios, "w");
	this->archivoPunteros = fopen(constantes::NombresArchivos::archivoPunteros, "w");
	this->archivoLexicoFC = fopen(constantes::NombresArchivos::archivoLexico,"w");
	this->tablaLexicoFC = fopen(constantes::NombresArchivos::archivoTablaLexico,"w");
	this->archivoPosRelativas = fopen(constantes::NombresArchivos::archivoPosicionesRelativas, "w");


}

void ParserDirectorio::parsearDirectorio(){
	this->parsearDirectorioRec(this->nombreDirectorio);
}

void ParserDirectorio::parsearDirectorioRec(char* directorioRuta){

	DIR *dir;
	struct dirent *dit;

	if ((dir = opendir(directorioRuta)) == NULL)
	{
		cout<<"El directorio "<<dit->d_name<<" no pudo a abrirse."<<endl;
	}

	int i;
	int offset=0;


	if (dir != NULL)
	{
		struct dirent* entry;
		while ((entry = readdir(dir))){
			if (!isCurrOrParentDir(entry->d_name)){ // Excluyo "." y ".."
				//Por cada archivo leido
				parser->resetUltimaPosicion();
				char* nombreDirectorio = entry->d_name;

				char ruta[1024]="";
				strcat(ruta, directorioRuta);
				strcat(ruta, "/");
				strcat(ruta, nombreDirectorio);
				FILE* dirAct = fopen(ruta, "r");

				struct stat st;
				lstat(ruta, &st);

				if(!S_ISDIR(st.st_mode)){
					//Guardo el nombre del archivo en archivoDirectorios.
					fputs(nombreDirectorio, this->archivoDirectorios);
					fputs(",", this->archivoDirectorios);

					//TODO variable a codificar en gamma (sería el archivo donde aparece)
					cout<<"Indexando directorio.."<<nombreDirectorio<<offset<<endl;


					parseFile(dirAct, offset);
					offset+= strlen(nombreDirectorio)+1;

				} else {
					parsearDirectorioRec(ruta);
				}

			}
		}
		closedir(dir);
	}
	abb::Nodo nod;
	//TODO ARREGLAR ESTA GUASADA
	//lo agregue porque al levantar el arbol misteriosamente no toma la ultima palabra. APCSC.
	nod.setPalabra("zzzzzzzzzzzzzzz");
	Posiciones* pos = new parser::Posiciones();
	pos->agregarPosicion(0);
	nod.setDocumentos(pos);
	nod.setPosiciones(pos);
	nod.setFrecuencias(pos);
	arbolito->insertar(nod);

	this->almacenarLexico();

	//CIERRO TOOOODO
	fclose(this->archivoDirectorios);
	fclose(this->archivoPunteros);
	fclose(this->archivoLexicoFC);
	fclose(this->tablaLexicoFC);
	fclose(this->archivoPosRelativas);

}

void ParserDirectorio::almacenarLexico(){
	punteros::PersistorPunteros PP(this->archivoPunteros, this->archivoPosRelativas);
	frontcoding::Frontcoding FC(this->archivoLexicoFC, this->tablaLexicoFC);
	arbolito->guardarLexico(FC, PP);
}



void ParserDirectorio::parseFile(FILE* dirAct, int offsetDocs){
	//Paso a abrir el directorio y parsearlo linea por linea
	char linea[LONG_MAX_LINEA];
	Posiciones posis;

	while (fgets(linea, LONG_MAX_LINEA, dirAct) != NULL){
		posis.resetCantidadPosiciones();

		string* parseo = this->parser->parsearLinea(linea,&posis, MAX_POSICIONES_LINEA);



		for (int i = 0; i<posis.getCantPosiciones(); i++) {

			//VEO SI YA ESTA EN EL ABB
			abb::Nodo nodotar;
			nodotar.setPalabra(parseo[i]);
			bool esta = arbolito->buscar(nodotar);

			//SI YA ESTA ACTUALIZO FRECUENCIA Y POSICIONES
			if (esta) {
				nodotar = arbolito->buscarYdevolver(nodotar);
				//Agrego su nro de palabra:
				nodotar.getPosiciones()->agregarPosicion(posis.getPosiciones()[i]);
				nodotar.setFrecuencia(nodotar.getFrecuencia()+1);
				nodotar.getDocumentos()->agregarPosicion(offsetDocs);
				this->arbolito->modify(nodotar);

			} else {
			//SI NO ESTA LO INSERTO.
				Posiciones* nuevosOffsetDocs = new Posiciones();
				Posiciones* nuevasPosiciones = new Posiciones();

				nuevasPosiciones->agregarPosicion(posis.getPosiciones()[i]);
				nuevosOffsetDocs->agregarPosicion(offsetDocs);

				nodotar.setFrecuencia(1);
				nodotar.setPosiciones(nuevasPosiciones);
				nodotar.setDocumentos(nuevosOffsetDocs);

				this->arbolito->insertar(nodotar);
			}

		}


	}

}
bool ParserDirectorio::isCurrOrParentDir(const string& name)
{
	return name == CURR_DIR_STR || name == PARENT_DIR_STR;
}

ParserDirectorio::~ParserDirectorio() {

	delete(parser);

}

} /* namespace parser */

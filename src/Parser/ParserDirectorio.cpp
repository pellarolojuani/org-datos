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

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

static const string CURR_DIR_STR = ".";
static const string PARENT_DIR_STR = "..";

namespace parser {

ParserDirectorio::ParserDirectorio(char* nombreDirectorio) {
	this->nombreDirectorio = nombreDirectorio;
	this->parser = new Parser();

	arbolito = new abb::ArbolB<abb::Nodo, ORDEN_NODO>;

	//TODO esto después cambiarlo
	this->archivoDirectorios = fopen("/home/lucia/directorios.dat","w");
	this->archivoPunteros = fopen("/home/lucia/punteros.dat","w");
	this->archivoLexicoFC = fopen("/home/lucia/archivoLexico.dat","w");
	this->tablaLexicoFC = fopen("/home/lucia/tablaLexico.dat","w");


}

int ParserDirectorio::parsearDirectorio(){
	this->parsearDirectorioRec(this->nombreDirectorio);
}

int ParserDirectorio::parsearDirectorioRec(char* directorioRuta){

	DIR *dir;
	struct dirent *dit;

	if ((dir = opendir(directorioRuta)) == NULL)
	{
		cout<<"El directorio "<<dit->d_name<<" no pudo a abrirse."<<endl;
		return -1;
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

					//TODO variable a codificar en gamma (sería el archivo donde aparece)
					cout<<"Indexando directorio.."<<nombreDirectorio<<offset<<endl;
					offset+= strlen(nombreDirectorio);

					parseFile(dirAct);

				} else {
					parsearDirectorioRec(ruta);
				}

			}
		}
		closedir(dir);
	}
	this->almacenarLexico();

}

void ParserDirectorio::almacenarLexico(){
	frontcoding::Frontcoding FC(this->archivoLexicoFC, this->tablaLexicoFC);
	arbolito->guardarLexico(FC);
}

void ParserDirectorio::parseFile(FILE* dirAct){
	//Paso a abrir el directorio y parsearlo linea por linea
	char linea[LONG_MAX_LINEA];
	Posiciones posis;
	while (fgets(linea, LONG_MAX_LINEA, dirAct) != NULL){
		posis.resetCantidadPosiciones();

		string* parseo = this->parser->parsearLinea(linea,&posis);

		for (int i = 0; i<posis.getCantPosiciones(); i++) {

			//VEO SI YA ESTA EN EL ABB
			abb::Nodo nodotar;
			nodotar.setPalabra(parseo[i]);
			bool esta = arbolito->buscar(nodotar);

			//SI YA ESTA ACTUALIZO FRECUENCIA Y POSICIONES
			if (esta) {
				nodotar = arbolito->buscarYdevolver(nodotar);
				nodotar.setFrecuencia(nodotar.getFrecuencia()+1);
				nodotar.getPosiciones().agregarPosicion(posis.getPosiciones()[i]);
				this->arbolito->modify(nodotar);

			} else {
			//SI NO ESTA LO INSERTO.
				Posiciones nuevasPosiciones;
				nuevasPosiciones.agregarPosicion(posis.getPosiciones()[i]);
				nodotar.setFrecuencia(1);
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
	// TODO Auto-generated destructor stub
}

} /* namespace parser */

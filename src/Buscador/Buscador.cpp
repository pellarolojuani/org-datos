/*
 * Buscador.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: lucia
 */

#include "Buscador.h"

#include <sstream>
#include <string>
#include "../Parser/Posiciones.h"
#include <stdlib.h>



//DEFINICION DUPLICADA
#ifndef LONG_MAX_LINEA
#define LONG_MAX_LINEA 200
#endif


namespace buscador {

Buscador::Buscador() {
	this->archivoLexico = fopen(constantes::NombresArchivos::archivoLexico,"rb");
	this->tablalexico = fopen(constantes::NombresArchivos::archivoTablaLexico,"rb");

	this->archivoPunteros = fopen(constantes::NombresArchivos::archivoPunteros,"rb");
	this->archivoPosiciones = fopen(constantes::NombresArchivos::archivoPosicionesRelativas,"rb");

	this->arbolB = new abb::ArbolB<abb::Nodo, ORDEN_NODO>();
	this->levantarArbol();
	arbolB->emitir();

}

abb::Nodo Buscador::buscarTermino(string term){

	abb::Nodo nodob;;
	nodob.setPalabra(term);

	if(arbolB->buscar(nodob)){
		nodob = arbolB->buscarYdevolver(nodob);
		Posiciones* documentos = new Posiciones();
		Posiciones* posiciones = new Posiciones();

		string* tokens;
		//SI EL OFFSET ME DA -1 ES PORQUE SE TRATA DE LA PRIMER PALABRA, Y COMO ESA LINEA NO LA
		//ESCRIBO EN LA TABLA, se lo tengo que avisar al seeker.
		cout<<"OFF "<<nodob.getLineaTabla()<<endl;
		int offset = nodob.getLineaTabla();
		if(offset != -1){
			char line[LONG_MAX_LINEA];
			fseek(this->tablalexico, nodob.getLineaTabla(),SEEK_SET);
			fgets(line,LONG_MAX_LINEA, this->tablalexico);
			tokens = parsearLinea(line);
		} else {
			tokens = parsearLinea("0,0,0,0");
			fseek(this->tablalexico, 0,SEEK_SET);
		}

		//La siguiente linea la uso para obtener el total de documentos.
		int longitud;
		char siguienteLinea[LONG_MAX_LINEA];
		if (!(fgets(siguienteLinea,LONG_MAX_LINEA, this->tablalexico)) == NULL){
			string* siguientesTok = parsearLinea(siguienteLinea);
			longitud = atoi(siguientesTok[2].c_str()) - atoi(tokens[2].c_str());
		} else {
			longitud = 999999999;
		}
		cout<<"OFFS: "<<offset<<endl;
		cout<<"LONG:  "<<longitud<<endl;

		//ME POSICIONO EN LOS ARCHIVOS DE PUNTEROS Y POSICIONES.
		fseek(this->archivoPunteros, atoi(tokens[2].c_str()), SEEK_SET);
		fseek(this->archivoPosiciones, atoi(tokens[3].c_str()), SEEK_SET);

		//LONGITUD: es la cantidad de caracteres que tienen los documentos.
		//Ahora es asi: documento1,frecuencia1,documento2,frecuencia2,..
		int i = 0;
		int docAnt=0;
		int sumaPosAnt=0;
		int sumaDocAnts=0;
		char c;
		while ((i<longitud)&&(c!=EOF)) {
			int doc;
			c = fgetc(this->archivoPunteros);
			i++;

			string strDoc;
			while((c!= ',')&&(i<longitud)){
				strDoc.append(toString(c));
				c = fgetc(this->archivoPunteros);
				i++;
			}
			doc = atoi(strDoc.c_str());
			documentos->agregarPosicion(doc+docAnt);
			docAnt+=doc;
			cout<<"DOC: "<<doc<<endl;
			//AHORA NECESITO LA FRECUENCIA PARA SABER CUANTAS POSICIONES TENGO QUE PARSEAR.
			c = fgetc(this->archivoPunteros);
			i++;
			int frec;
			string strFrec;
			while((c!= ',')&&(i<longitud)){
				strFrec.append(toString(c));
				c = fgetc(this->archivoPunteros);
				i++;
			}


			//GUARDO LA FRECUENCIA SIGUIENTE AL NRO DE OFFSET DE DOCUMENTO
			cout<<"FREC:"<<strFrec<<endl;
			frec = atoi(strFrec.c_str());
			documentos->agregarPosicion(frec);

			//Frec me dice la cantidad de posiciones que tengo que parsear de el archivo de posiciones para el documento doc.
			int j = 0;
			sumaPosAnt = 0;
			while ((j<frec)){
				//PARSEO CADA POSICION
				char c2 = fgetc(this->archivoPosiciones);
				string strPos;
				while(c2!= ','){
					strPos.append(toString(c2));
					c2 = fgetc(this->archivoPosiciones);
				}
				int pos = atoi(strPos.c_str());
				posiciones->agregarPosicion(pos+sumaPosAnt);
				sumaPosAnt=pos+sumaPosAnt;

				j++;
			}

		}
		nodob.setPosiciones(posiciones);
		nodob.setDocumentos(documentos);
	} else
		return nodob;
	return nodob;
}

string Buscador::toString(char c){
	stringstream s0;
	string lineaStr;
	s0 << c;
	s0 >> lineaStr;
	return lineaStr;
}

string* Buscador::parsearLinea(char* line){
	parser::Parser pars;
	stringstream s0;
	string lineaStr;
	s0 << line;
	s0 >> lineaStr;
	cout<<lineaStr<<endl;
	Posiciones pos;
	string* tokens;
	tokens = pars.parsearLinea(lineaStr, &pos);
	return tokens;

}

void Buscador::levantarArbol(){
	char linea[LONG_MAX_LINEA];
	string palabraAnterior = "";
	//Tengo que agarrar la primera.


	int offset = 0;
	int offsetAnterior = 0;

	Parser pars;
	Posiciones p;
	int posicionAnterior = 0;
	int iguales = 0;

	bool esPrimerPalabra = true;

	while (fgets(linea, LONG_MAX_LINEA, this->tablalexico) != NULL){
		cout<<offset<<endl;
		abb::Nodo nuevoNodo;
		p.resetCantidadPosiciones();
		//AGARRO LA SIGUIENTE LINEA Y LA TENGO QUE COMPARAR CON LA ANTERIOR PARA SACAR LA LONGITUD DE LA PALABRA
		string* tokens = pars.parsearLinea(linea, &p);

		//Horrible implemetacion de split:
		stringstream s0;
		string lineaStr;
		s0 << linea;
		s0 >> lineaStr;
		cout<<lineaStr<<endl;
		int j=0;
		for(int i=0; lineaStr[i]!=','; i++){
			j++;
		}
		int posicionSig = atoi(tokens[0].c_str());

		//LA LONG DEL ANTERIOR ES LA POSICION ACTUAL MENOS LA ANTERIOR.
		int longitud = posicionSig - posicionAnterior;

		//LOS CARACTERES IGUALES VIENEN DEL ANTERIOR, TODAVIA NO HAY QUE ACTUALIZARLOS
		fseek(this->archivoLexico, posicionAnterior, SEEK_SET);
		char* buffer = (char*) malloc (sizeof(char)*longitud);
		//LEO LA CADENA QUE NECESITO
		size_t result = fread (buffer,1,longitud,this->archivoLexico);

		//ME ARMO LA PALABRA EN BASE AL LA ANTERIOR
		stringstream ss;
		string strCharsDistintos;
		ss << buffer;
		ss >> strCharsDistintos;
		strCharsDistintos = strCharsDistintos.substr(0, longitud);
		string comienzoPalabra = palabraAnterior.substr(0,iguales);

		string fin = strCharsDistintos;
		std::stringstream s2;
		s2 << comienzoPalabra << fin;
		std::string strPalabra = s2.str();

		//LE PONGO TODAS LAS PROPIEDADES
		nuevoNodo.setPalabra(strPalabra);

		//agregando chanchadas al tp.
		//Si es la primer palabra (dado que no consideramos la linea (0,0,0,0), le ponemos un offset de -1
		//indicando que cuando lo agarre sepa que la linea es (0,0,0,0).
		if(esPrimerPalabra){
			nuevoNodo.setLineaTabla(-1);
			esPrimerPalabra = false;
		} else
			nuevoNodo.setLineaTabla(offset-lineaStr.length());

//		cout<<"PAL:   "<<strPalabra<<"   ||     "<<"OFFSET  "<<offset-lineaStr.length()<<endl;

		//FINALMENTE LO INSERTO EN EL ARBOL B
		arbolB->insertar(nuevoNodo);

		//ACTUALIZO TOOOOODO
		palabraAnterior = strPalabra;
		iguales = atoi(lineaStr.substr(j+1, lineaStr.length()).c_str());
		posicionAnterior = posicionSig;
		offset=ftell(this->tablalexico);
		offsetAnterior=offset;

		free(buffer);
	}
}



Buscador::~Buscador() {
	// TODO Auto-generated destructor stub
}

} /* namespace buscador */
